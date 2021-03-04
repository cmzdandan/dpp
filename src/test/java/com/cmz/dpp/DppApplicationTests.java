package com.cmz.dpp;

import com.cmz.dpp.mock.MockDataFromFile;
import com.cmz.dpp.service.DppService;
import org.junit.jupiter.api.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import java.util.List;

@RunWith(SpringJUnit4ClassRunner.class)
@SpringBootTest
class DppApplicationTests {

	@Autowired
	private DppService dppService;

	@Test
	void dppTest() {
		MockDataFromFile mockData = new MockDataFromFile();
		mockData.initGoodsInfo(mockData.getGoodsFile());
		System.out.println("begin call dpp");
		List<String> result = dppService.reArrange(100, mockData.getGoodsInfoList());
		System.out.println("finished dpp. " + result);
	}

}
