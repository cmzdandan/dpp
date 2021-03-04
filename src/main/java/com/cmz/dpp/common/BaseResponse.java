package com.cmz.dpp.common;

import lombok.Data;

/**
 * @author cobin.chen DPP算法返回体
 */
@Data
public class BaseResponse {

	private int code = CodeEnum.OK.getCode();

	private String msg;

	private Object data;

	public BaseResponse() {
	}

	public BaseResponse(CodeEnum codeEnum, String msg) {
		this.code = codeEnum.getCode();
		this.msg = msg;
	}

	public BaseResponse(CodeEnum codeEnum, Object data) {
		this.code = codeEnum.getCode();
		this.data = data;
	}

	public BaseResponse(Object data) {
		this.data = data;
	}

	@Override
	public String toString() {
		return "BaseResponse{" + "code=" + code + ", msg='" + msg + '\'' + ", data=" + data + '}';
	}

}
