package com.cmz.dpp.controller;

import com.cmz.dpp.common.BaseResponse;
import com.cmz.dpp.common.CodeEnum;
import com.cmz.dpp.common.DppRequest;
import com.cmz.dpp.model.GoodsInfo;
import com.cmz.dpp.service.DppService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.util.CollectionUtils;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

/**
 * @author cobin.chen Dpp服务访问入口
 */
@RestController
@RequestMapping("/dpp")
public class DppController {

	@Autowired
	private DppService dppService;

	@PostMapping(value = "/reArrange")
	public BaseResponse reArrange(@RequestBody DppRequest request) {
		List<GoodsInfo> goodsInfoList = request.getGoodsInfoList();
		if (CollectionUtils.isEmpty(goodsInfoList)) {
			return new BaseResponse(CodeEnum.INVALID_PARAM);
		}
		List<String> result = dppService.reArrange(request.getTopN(), goodsInfoList);
		return new BaseResponse(result);
	}

}
