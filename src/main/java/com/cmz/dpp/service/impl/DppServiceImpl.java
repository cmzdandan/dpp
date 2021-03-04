package com.cmz.dpp.service.impl;

import com.cmz.dpp.mapper.SpuVectorMapper;
import com.cmz.dpp.mock.MockDataFromFile;
import com.cmz.dpp.mock.MockFeatures;
import com.cmz.dpp.mock.MockScores;
import com.cmz.dpp.mock.MockSpuIds;
import com.cmz.dpp.model.GoodsInfo;
import com.cmz.dpp.model.SpuVector;
import com.cmz.dpp.service.DppService;
import com.cmz.dpp.utils.DppAlgorithm;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.CollectionUtils;

import javax.annotation.PostConstruct;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * @author cobin.chen Dpp服务业务类
 */
@Service
public class DppServiceImpl implements DppService {

	private static final Logger logger = LoggerFactory.getLogger(DppServiceImpl.class);

	private Map<String, float[]> map;

	@Autowired
	private SpuVectorMapper spuVectorMapper;

	@Autowired
	private DppAlgorithm dppAlgorithm;

	@PostConstruct
	public void loadSpuFeatures() {
		logger.info("loading spu features...");
		int count = spuVectorMapper.count();
		map = new ConcurrentHashMap<>((count << 2) / 3);
		int pageSize = 10000;
		int remainder = count % pageSize;
		int quotient = count / pageSize;
		int pageTotal = (remainder == 0) ? quotient : quotient + 1;
		logger.info("pageTotal: {}", pageTotal);
		ExecutorService executorService = Executors.newFixedThreadPool(10);
		for (int pageNum = 0; pageNum < pageTotal; pageNum++) {
			int finalPageNum = pageNum;
			executorService.submit(() -> {
				initSpuFeatures(map, finalPageNum, pageSize);
				System.out.println("now page: " + finalPageNum);
			});
		}
		logger.info("load spu features finished.");
	}

	private void initSpuFeatures(Map map, int pageNum, int pageSize) {
		List<SpuVector> spuVectors = spuVectorMapper.selectSpuVectorInfosByPage(pageNum * pageSize, pageSize);
		if (CollectionUtils.isEmpty(spuVectors)) {
			return;
		}
		int length;
		for (SpuVector spuVector : spuVectors) {
			String spuId = spuVector.getSpuId();
			String[] vectors = spuVector.getVec().split(",");
			length = vectors.length;
			float[] features = new float[length];
			for (int i = 0; i < length; i++) {
				features[i] = Float.valueOf(vectors[i]);
			}
			map.put(spuId, features);
		}
	}

	@Override
	public List<String> reArrange(int topN, List<GoodsInfo> goodsInfoList) {
		// 保留一份spu的初始排序集合
		List<String> srcSpuList = goodsInfoList.stream().map(GoodsInfo::getSpuId).collect(Collectors.toList());
		List<GoodsInfo> subList;
		if (goodsInfoList.size() > topN) {
			// 对goodsInfoList按分数从高到低排序
			Collections.sort(goodsInfoList, (x, y) -> y.getScore() - x.getScore() >= 0 ? 1 : -1);
			// 取300个商品进行多样性排序
			subList = goodsInfoList.stream().limit(300).collect(Collectors.toList());
		} else {
			subList = goodsInfoList;
		}
		 List<String> selected = mock();// 用于验证正确性
//		List<String> selected = doSelect(topN, subList);
		// 未选中的spu集合
		List<String> remainingList = srcSpuList.stream().filter(s -> selected.contains(s)).collect(Collectors.toList());
		// 合并两个集合并去重
		return Stream.of(selected, remainingList).flatMap(Collection::stream).distinct().collect(Collectors.toList());
	}

	private List<String> doSelect(int topN, List<GoodsInfo> goodsInfos) {
		int length = goodsInfos.size();
		List<String> spuIds = new ArrayList<>();
		float[] scores = new float[length];
		float[][] features = new float[length][];
		GoodsInfo goodsInfo;
		for (int i = 0; i < length; i++) {
			goodsInfo = goodsInfos.get(i);
			String spuId = goodsInfo.getSpuId();
			spuIds.add(spuId);
			scores[i] = goodsInfo.getScore();
			features[i] = map.get(spuId);
		}
		return dppAlgorithm.select(topN, spuIds, scores, features);
	}

	/**
	 * 用于验证准确性
	 * @return
	 */
	private List<String> mock() {
		int topN = 10;
		List<String> spuIds = MockSpuIds.spuIds();
		float[] scores = MockScores.score100();
		float[][] features = MockFeatures.feature100Times8();
		Map<String, Object> costMap = new HashMap<>();
		return dppAlgorithm.select(topN, spuIds, scores, features);
	}

	/**
	 * 用于测试性能
	 * @return
	 */
	private List<String> mockRandom() {
		int topN = 100;
		MockDataFromFile mockData = new MockDataFromFile();
		mockData.initGoodsInfo(mockData.getGoodsFile());
		mockData.initFeature(mockData.getFeatureFile());
		Random random = new Random();
		int skip = random.nextInt(1000);
		List<GoodsInfo> goodsInfos = mockData.getGoodsInfoList().stream().skip(skip).limit(300)
				.collect(Collectors.toList());
		int length = goodsInfos.size();
		List<String> spuIds = new ArrayList<>();
		float[] scores = new float[length];
		float[][] features = MockFeatures.feature100Times8();
		GoodsInfo goodsInfo;
		for (int i = 0; i < length; i++) {
			goodsInfo = goodsInfos.get(i);
			String spuId = goodsInfo.getSpuId();
			spuIds.add(spuId);
			scores[i] = goodsInfo.getScore();
		}
		long begin = System.currentTimeMillis();
		Map<String, Object> costMap = new HashMap<>();
		List<String> selectedSpuIds = dppAlgorithm.select(topN, spuIds, scores, features);
		logger.info("cost: {}", System.currentTimeMillis() - begin);
		return selectedSpuIds;
	}

}
