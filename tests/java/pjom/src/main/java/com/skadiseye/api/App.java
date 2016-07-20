package com.skadiseye.api;

/**
 * Hello world!
 * 
 * mvn install -Dmaven.test.skip=true 
 * mvn exec:java -Dexec.mainClass="com.skadiseye.api.App" -Dexec.classpathScope=runtime
 * 
 * 如果jar里没有 manifest，则可以使用 java -cp 。。。.jar com.skadiseye.api.App
 * 
 * 当main类依赖多个jar时，可以把多个jar打包到一个目录，然后用-Djava.ext.dirs指定该目录，引用依赖的多个jar，
 * java -Djava.ext.dirs=./target com.skadiseye.api.App
 */
public class App {
    public static void main(String[] args) {
	while (true) {

	    System.out.println("我操你妈。。。。。。。。。。。。。。。。。。。");
	    try {
		Thread.sleep(1000);
	    } catch (InterruptedException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	    }
	}

    }
}
