package com.cmz.dpp.service;

import com.cmz.dpp.model.GoodsInfo;

import java.util.List;

/**
 * @author cobin.chen
 */
public interface DppService {

	List<String> reArrange(int topN, List<GoodsInfo> goodsInfoList);

}
