package com.cmz.dpp.utils;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;
import org.springframework.util.StringUtils;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.*;

/**
 * @author cobin.chen 多样性算法DPP
 * 多线程计算相似矩阵
 * 多线程计算核矩阵
 * 每一个线程计算若干行
 * DPP计算中使用 System.arraycopy 替换for循环赋值
 * 自己声明静态线程池，不适用SpringBoot托管线程池，减少了动态代理带来的额外开销
 */
@Component
public class DppAlgorithm {

	private static final Logger logger = LoggerFactory.getLogger(DppAlgorithm.class);

	private static final int threadNum = 10;

	private static final int corePoolSize = 8;

	private static final int maximumPoolSize = 16;

	private static final int keepAliveTime = 1;

	private static final int capacity = 5000;

	private static ExecutorService threadPool = new ThreadPoolExecutor(corePoolSize, maximumPoolSize, keepAliveTime,
			TimeUnit.SECONDS, new LinkedBlockingDeque<>(capacity));

	/**
	 * @param topN
	 * @param spuIds
	 * @param scores
	 * @param featureMatrix
	 * @return 经过DPP算法重排后最优的topN个spuId数组
	 */
	public List<String> select(int topN, List<String> spuIds, float[] scores, float[][] featureMatrix) {
		try {
			float epsilon = 1e-10F;
			// 构造相似矩阵
			float[][] similarities = calculateSimilarities(featureMatrix);
			// 构造核矩阵
			float[][] kernelMatrix = calculateKernelMatrix(scores, similarities);
			// 调用DPP算法，选出指定个合适的SPU
			return selectByDpp(kernelMatrix, spuIds, topN, epsilon);
		} catch (InterruptedException e) {
			logger.error("error happened.", e);
			// 如果碰到spu对应的特征向量没有加载到内存则有可能出现计算时抛异常，直接原序返回
			return spuIds;
		}
	}

	/**
	 * 通过DPP算法，选取指定个数的合适的SPU出来，以数组形式返回
	 */
	private List<String> selectByDpp(float[][] kernelMatrix, List<String> spuIds, int topN, float epsilon) {
		int spuIdNum = kernelMatrix.length;
		float[] eis = new float[spuIdNum];
		float[][] cis = new float[topN][spuIdNum];
		List<String> selectedSpuList = new ArrayList();
		float[] di2s = new float[spuIdNum];
		int selectedItemIndex = fetchDi2sAndFindMaxIndex(spuIdNum, di2s, kernelMatrix);
		String selectedSpu = spuIds.get(selectedItemIndex);
		if (StringUtils.isEmpty(selectedSpu)) {
			selectedSpuList.add(selectedSpu);
		}
		int index = 1;
		while (index < topN) {
			int k = index - 1;
			// ci_optimal
			float[] ciOptimal = fetchCiOptimal(k, selectedItemIndex, cis);
			// di_optimal
			float diOptimal = (float) Math.sqrt(di2s[selectedItemIndex]);
			// elements
			float[] elements = fetchElements(selectedItemIndex, kernelMatrix);
			// eis
			calculateEis(spuIdNum, k, ciOptimal, cis, elements, diOptimal, eis);
			// update cis
			updateCisByEis(k, spuIdNum, cis, eis);
			// update di2s and find optimal value index
			selectedItemIndex = updateDi2sByEisAndFindMaxIndex(spuIdNum, di2s, eis);
			if (di2s[selectedItemIndex] < epsilon) {
				break;
			}
			selectedSpu = spuIds.get(selectedItemIndex);
			if (StringUtils.isEmpty(selectedSpu)) {
				selectedSpuList.add(selectedSpu);
			}
		}
		return selectedSpuList;
	}

	// 更新di2s，同时找到最佳元素的下标
	private int updateDi2sByEisAndFindMaxIndex(int spuIdNum, float[] di2s, float[] eis) {
		float maxValue = Float.MIN_VALUE;
		int index = 0;
		for (int i = 0; i < spuIdNum; i++) {
			di2s[i] -= eis[i] * eis[i];
			if (di2s[i] > maxValue) {
				maxValue = di2s[i];
				index = i;
			}
		}
		return index;
	}

	// 更新cis 将 eis 赋值给 cis 的第 k 行
	private void updateCisByEis(int k, int spuIdNum, float[][] cis, float[] eis) {
		System.arraycopy(eis, 0, cis[k], 0, spuIdNum);
	}

	// 计算eis
	private void calculateEis(int spuIdNum, int k, float[] ciOptimal, float[][] cis, float[] elements, float diOptimal,
			float[] eis) {
		for (int i = 0; i < spuIdNum; i++) {
			float rt = 0;
			for (int j = 0; j < k; j++) {
				rt += ciOptimal[j] * cis[j][i];
			}
			eis[i] = (elements[i] - rt) / diOptimal;
		}
	}

	// 提取核矩阵中被选中的元素所在的行的所有元素
	private float[] fetchElements(int selectedItemIndex, float[][] kernelMatrix) {
		int length = kernelMatrix.length;
		float[] result = new float[length];
		System.arraycopy(kernelMatrix[selectedItemIndex], 0, result, 0, length);
		return result;
	}

	// 提取 ci_optimal
	private float[] fetchCiOptimal(int k, int selectedItemIndex, float[][] cis) {
		float[] result = new float[k];
		for (int i = 0; i < k; i++) {
			result[i] = cis[i][selectedItemIndex];
		}
		return result;
	}

	// 提取核矩阵的对角元素，同时找到最佳元素的下标
	private int fetchDi2sAndFindMaxIndex(int length, float[] di2s, float[][] kernelMatrix) {
		float maxValue = Float.MIN_VALUE;
		int index = 0;
		for (int i = 0; i < length; i++) {
			di2s[i] = kernelMatrix[i][i];
			if (di2s[i] > maxValue) {
				maxValue = di2s[i];
				index = i;
			}
		}
		return index;
	}

	/**
	 * 计算核矩阵
	 * score.reshape((item_size, 1)) * similarities * score.reshape((1, item_size))
	 * 输入的相似矩阵是 m×m
	 * m就等于输入的spuId个数，即 item_size
	 * scores本身就是一个一维数组，可以看做是 1行m列
	 * score.reshape((item_size, 1))：将scores变成 m行1列的矩阵
	 * score.reshape((1, item_size))：将scores变成 1行m列的矩阵
	 *
	 * 相似矩阵的每一项乘了下分数以及分数的转置，得到核矩阵
	 * 最终输出的还是 m行m列的 矩阵
	 * 核矩阵也是一个方阵
	 *
	 * 多个线程，对相似矩阵进行切片并行计算，将计算结果填充到核矩阵
	 */
	private float[][] calculateKernelMatrix(float[] scores, float[][] similarities) throws InterruptedException {
		int row = similarities.length;
		float[][] kernelMatrix = new float[row][row];
		int remainder = row % threadNum;
		int quotient = row / threadNum;
		int segment = (remainder == 0) ? quotient : quotient + 1;
		CountDownLatch countDownLatch = new CountDownLatch(threadNum);
		for (int loop = 0; loop < similarities.length; loop++) {
			int finalLoop = loop;
			threadPool.submit(() -> doCalculateKernelMatrix(segment, finalLoop, row, kernelMatrix, scores, similarities,
					countDownLatch));
		}
		countDownLatch.await();
		return kernelMatrix;
	}

	private void doCalculateKernelMatrix(int segment, int loop, int row, float[][] kernelMatrix, float[] scores,
			float[][] similarities, CountDownLatch countDownLatch) {
		for (int rowNum = segment * loop; rowNum < segment * (loop + 1) && rowNum < row; rowNum++) {
			for (int colNum = 0; colNum < row; colNum++) {
				kernelMatrix[rowNum][colNum] = scores[rowNum] * similarities[rowNum][colNum] * scores[colNum];
			}
		}
		countDownLatch.countDown();
	}

	/**
	 * 根据特征矩阵计算相似矩阵
	 * np.dot(feature_vectors, feature_vectors.T)
	 * 特征矩阵(m×n) 点乘 特征矩阵的转置(n×m)
	 * 得到的结果是 m×m 矩阵(行列数相等，是一个方阵)
	 * m等于输入的spuId个数
	 *
	 * 多个线程，对特征矩阵进行切片并行计算，将计算结果填充到相似矩阵
	 */
	private float[][] calculateSimilarities(float[][] featureMatrix) throws InterruptedException {
		int row = featureMatrix.length;
		int dimension = featureMatrix[0].length;
		float[][] similarities = new float[row][row];
		int remainder = row % threadNum;
		int quotient = row / threadNum;
		int segment = (remainder == 0) ? quotient : quotient + 1;
		CountDownLatch countDownLatch = new CountDownLatch(threadNum);
		for (int loop = 0; loop < threadNum; loop++) {
			int finalLoop = loop;
			threadPool.submit(() -> doCalculateSimilarities(segment, finalLoop, row, dimension, similarities,
					featureMatrix, countDownLatch));
		}
		countDownLatch.await();
		return similarities;
	}

	private void doCalculateSimilarities(int segment, int loop, int row, int dimension, float[][] similarities,
			float[][] featureMatrix, CountDownLatch countDownLatch) {
		for (int rowNum = segment * loop; rowNum < segment * (loop + 1) && rowNum < row; rowNum++) {
			for (int colNum = 0; colNum < row; colNum++) {
				for (int k = 0; k < dimension; k++) {
					similarities[rowNum][colNum] += featureMatrix[rowNum][k] * featureMatrix[colNum][k];
				}
			}
		}
		countDownLatch.countDown();
	}

}
