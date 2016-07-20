# PHP 

# 调用 Java 项目 pjom

> - ##### php拓展编译
>
> ```shell
> ./configure --prefix=/pom/php/  --with-php-config=/pom/php/bin/php-config
> make
> make install
>
> /pom/php/bin/php-cgi pjom.php
>
> service httpd restart
> www.skadiseye.wang/info.php
> ```
>
> - #### C++调用java代码
>
> >- ###### 参考资料
> >
> >http://blog.sina.com.cn/s/blog_48eef8410100fjxr.html
>
>
>
> > - jar cvf test.jar *



> > -  ​
> >
> > ```shell
> > g++ -o testjava main.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/amd64/server -ljvm
> > ```


> - #### 目前适用 命令行模式  和 nginx模式
>
>   ​