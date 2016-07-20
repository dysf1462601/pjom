package com.test;
public class MyTest {
	public MyTest(){
		super();
	}

	//给php调用的类
	public String pom_pjom(String json_str)
	{
		String retStr = "{\"data\":\"我我操你麻痹\",\"info\":\"call success!\",\"status\":100}";
		return retStr;
	}
}