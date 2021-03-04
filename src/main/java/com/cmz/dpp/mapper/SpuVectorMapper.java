package com.cmz.dpp.mapper;

import com.cmz.dpp.model.SpuVector;
import org.apache.ibatis.annotations.Param;
import tk.mybatis.mapper.common.Mapper;

import java.util.List;

public interface SpuVectorMapper extends Mapper<SpuVector> {

	int count();

	List<SpuVector> selectSpuVectorInfosByPage(@Param("from") int from, @Param("size") int size);

}