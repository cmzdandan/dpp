package com.cmz.dpp.model;

import lombok.Data;

import javax.persistence.Column;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;
import java.util.Date;

@Data
@Table(name = "vector_recall")
public class SpuVector {
	/**
	 * 自增ID
	 */
	@Id
	@GeneratedValue(generator = "JDBC")
	private Long id;

	/**
	 * SPU ID
	 */
	@Column(name = "spu_id")
	private String spuId;

	/**
	 * SPU Vector
	 */
	private String vec;

	/**
	 * 修改时间
	 */
	@Column(name = "update_time")
	private Date updateTime;

}