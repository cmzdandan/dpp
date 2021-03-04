package com.cmz.dpp.mock;

import com.alibaba.fastjson.JSON;
import com.cmz.dpp.model.GoodsInfo;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * @author cobin.chen
 */
public class MockDataFromFile {

	private static List<GoodsInfo> goodsInfoList = new ArrayList<>();

	private static float[][] features = new float[300][];

	private static String goodsFile = MockDataFromFile.class.getClassLoader().getResource("mock/spuScores.json")
			.getPath();

	private static String featureFile = MockDataFromFile.class.getClassLoader().getResource("mock/feature.txt")
			.getPath();


	public String getGoodsFile() {
		return goodsFile;
	}

	public String getFeatureFile() {
		return featureFile;
	}

	public List<GoodsInfo> getGoodsInfoList() {
		return goodsInfoList;
	}

	public void initGoodsInfo(String fileName) {
		File file = new File(fileName);
		BufferedReader reader = null;
		try {
			reader = new BufferedReader(new FileReader(file));
			String line;
			while ((line = reader.readLine()) != null) {
				goodsInfoList.add(JSON.parseObject(line, GoodsInfo.class));
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (reader != null) {
				try {
					reader.close();
				} catch (IOException e1) {
					e1.printStackTrace();
				}
			}
		}
	}

	public void initFeature(String fileName) {
		File file = new File(fileName);
		BufferedReader reader = null;
		try {
			Random random = new Random();
			int nextInt = random.nextInt(20);
			reader = new BufferedReader(new FileReader(file));
			String line;
			int index = 0;
			while (index < 300 && (line = reader.readLine()) != null) {
				if (nextInt < 6) {
					nextInt = random.nextInt(20);
					continue;
				}
				String[] featureArray = line.split(",");
				float[] temp = new float[featureArray.length];
				for (int i = 0; i < featureArray.length; i++) {
					temp[i] = Float.valueOf(featureArray[i]);
				}
				features[index++] = temp;
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (reader != null) {
				try {
					reader.close();
				} catch (IOException e1) {
					e1.printStackTrace();
				}
			}
		}
	}

}
