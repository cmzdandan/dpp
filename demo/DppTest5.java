package com.cmz.test.matrix;

import java.time.Duration;
import java.time.Instant;
import java.util.Arrays;
import java.util.stream.IntStream;

/**
 * @author cobin.chen
 */
public class DppTest5 {

	/************************
	 * 每个商品SPU都有一个ID，有一个分数，有一个特征向量，可以包装成如下的几个成员变量
	 * String spuId;
	 * float score;
	 * float[] features;
	 *
	 * DPP算法，要从多个SPU中，挑选出指定个合适的SPU出来
	 ************************/

	public static void main(String[] args) {
		// 期望挑出的spu个数
		int maxLength = 10;
		String[] spuIds = MockDataSpuIds.spuIds100();
		float[] scores = MockData100Times8Float.mockScores();
		float[][] featureMatrix = MockData100Times8Float.mockFeatureMatrix();
		String[] result = select(maxLength, spuIds, scores, featureMatrix);
		System.out.println(Arrays.toString(result));
	}

	private static String[] select(int maxLength, String[] spuIds, float[] scores, float[][] featureMatrix) {
		float epsilon = 1e-10F;
		Instant instant1 = Instant.now();
		// 构造相似矩阵
		float[][] similarities = calculateSimilarities(featureMatrix);
		Instant instant2 = Instant.now();
		System.out.println("构造相似矩阵: " + Duration.between(instant1, instant2).toMillis());
		// 构造核矩阵
		float[][] kernelMatrix = calculateKernelMatrix(scores, similarities);
		Instant instant3 = Instant.now();
		System.out.println("构造核矩阵: " + Duration.between(instant2, instant3).toMillis());
		// 调用DPP算法，选出指定个合适的SPU
		String[] selectedSpuIds = selectByDpp(kernelMatrix, spuIds, maxLength, epsilon);
		Instant instant4 = Instant.now();
		System.out.println("DPP算法: " + Duration.between(instant3, instant4).toMillis());
		return selectedSpuIds;
	}

	/**
	 * 通过DPP算法，选取指定个数的合适的SPU出来，以数组形式返回
	 */
	private static String[] selectByDpp(float[][] kernelMatrix, String[] spuIds, int maxLength, float epsilon) {
		int spuIdNum = kernelMatrix.length;
		// get cis 构造一个全0的矩阵
		float[][] cis = new float[maxLength][spuIdNum];
		// get di2s 核矩阵的对角元素
		float[] di2s = fetchDi2s(kernelMatrix);
		String[] selectedItems = new String[maxLength];
		int selectedItemIndex = getMaxValueIndex(di2s);
		selectedItems[0] = spuIds[selectedItemIndex];
		float[] eis = new float[spuIdNum];
		int index = 1;
		while (index < maxLength) {
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
			// update di2s
			updateDi2sByEis(spuIdNum, di2s, eis);
			// update selected_items
			selectedItemIndex = getMaxValueIndex(di2s);
			if (di2s[selectedItemIndex] < epsilon) {
				break;
			}
			selectedItems[index] = spuIds[selectedItemIndex];
			index++;
		}
		return selectedItems;
	}

	// 更新di2s
	private static void updateDi2sByEis(int spuIdNum, float[] di2s, float[] eis) {
		for (int i = 0; i < spuIdNum; i++) {
			di2s[i] -= eis[i] * eis[i];
		}
	}

	// 更新cis
	private static void updateCisByEis(int k, int spuIdNum, float[][] cis, float[] eis) {
		for (int i = 0; i < spuIdNum; i++) {
			cis[k][i] = eis[i];
		}
	}

	// 计算eis
	private static void calculateEis(int spuIdNum, int k, float[] ciOptimal, float[][] cis, float[] elements,
			float diOptimal, float[] eis) {
		for (int i = 0; i < spuIdNum; i++) {
			float rt = 0;
			for (int j = 0; j < k; j++) {
				rt += ciOptimal[j] * cis[j][i];
			}
			eis[i] = (elements[i] - rt) / diOptimal;
		}
	}

	// 提取核矩阵中选中的元素
	private static float[] fetchElements(int selectedItemIndex, float[][] kernelMatrix) {
		int length = kernelMatrix.length;
		float[] result = new float[length];
		for (int i = 0; i < length; i++) {
			result[i] = kernelMatrix[selectedItemIndex][i];
		}
		return result;
	}

	// 提取 ci_optimal
	private static float[] fetchCiOptimal(int k, int selectedItemIndex, float[][] cis) {
		float[] result = new float[k];
		for (int i = 0; i < k; i++) {
			result[i] = cis[i][selectedItemIndex];
		}
		return result;
	}

	/**
	 * 从一个数组中找到最大值，返回其下标
	 */
	private static int getMaxValueIndex(float[] array) {
		return IntStream.range(0, array.length).reduce((i, j) -> array[i] > array[j] ? i : j).getAsInt();
	}

	// 提取核矩阵的对角元素
	private static float[] fetchDi2s(float[][] kernelMatrix) {
		int row = kernelMatrix.length;
		float[] result = new float[row];
		for (int i = 0; i < row; i++) {
			result[i] = kernelMatrix[i][i];
		}
		return result;
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
	 */
	private static float[][] calculateKernelMatrix(float[] scores, float[][] similarities) {
		int row = similarities.length;
		int column = similarities.length;
		float[][] result = new float[row][column];
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				result[i][j] = scores[i] * similarities[i][j] * scores[j];
			}
		}
		return result;
	}

	/**
	 * 根据特征矩阵计算相似矩阵
	 * np.dot(feature_vectors, feature_vectors.T)
	 * 特征矩阵(m×n) 点乘 特征矩阵的转置(n×m)
	 * 得到的结果是 m×m 矩阵(行列数相等，是一个方阵)
	 * m等于输入的spuId个数
	 */
	private static float[][] calculateSimilarities(float[][] featureMatrix) {
		// 特征矩阵的行数
		int row = featureMatrix.length;
		int column = featureMatrix.length;
		// 特征矩阵的列数
		int featureDimension = featureMatrix[0].length;
		float[][] result = new float[row][column];
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				for (int k = 0; k < featureDimension; k++) {
					result[i][j] += featureMatrix[i][k] * featureMatrix[j][k];
				}
			}
		}
		return result;
	}

}
