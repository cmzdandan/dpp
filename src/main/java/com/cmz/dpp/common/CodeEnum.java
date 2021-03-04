package com.cmz.dpp.common;

/**
 * @author cobin.chen 返回码枚举
 */
public enum CodeEnum {

	OK(200, "成功"),

	INVALID_PARAM(400, "参数异常"),

	INTERNAL_SERVER_ERROR(500, "内部错误");

	private int code;

	private String msg;

	CodeEnum(int code, String msg) {
		this.code = code;
		this.msg = msg;
	}

	public String getMsg() {
		return msg;
	}

	public int getCode() {
		return code;
	}

	public static CodeEnum valueOf(int code) {
		for (CodeEnum codeEnum : CodeEnum.values()) {
			if (codeEnum.code == code) {
				return codeEnum;
			}
		}
		return null;
	}

	@Override
	public String toString() {
		return "CodeEnum{" + "code=" + code + ", msg='" + msg + '\'' + "} " + super.toString();
	}

}
