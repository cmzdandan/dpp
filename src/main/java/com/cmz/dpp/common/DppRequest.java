package com.cmz.dpp.common;

import com.cmz.dpp.model.GoodsInfo;
import lombok.Data;

import java.util.List;

/**
 * @author cobin.chen Dpp请求体
 */
@Data
public class DppRequest {

	private List<GoodsInfo> goodsInfoList;

	private int topN = 100;

	@Override
	public String toString() {
		return "DppRequest{" + "topN='" + topN + '\'' + ", goodsInfoList=" + goodsInfoList + '}';
	}

}
