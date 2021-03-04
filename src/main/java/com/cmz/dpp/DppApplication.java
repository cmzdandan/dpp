package com.cmz.dpp;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import tk.mybatis.spring.annotation.MapperScan;

@SpringBootApplication
@MapperScan("com.cmz.dpp.mapper")
public class DppApplication {

	public static void main(String[] args) {
		SpringApplication.run(DppApplication.class, args);
	}

}
