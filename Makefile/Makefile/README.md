**对于Make file的详细记以及说明**
* 第一行参数 CFLAGS:如笔记上所说，是编译器参数。
	**设置为**


			 -g -O2 -Wall -Wextra -Isrc -rdynamic 
			 -g是 关闭所有的优化机制，以便程序执行过程中严格按照原来的C代码进行
			 -O2 值优化等级
			 -Wall 生成所有警告信息 
			 -Wextra 启用一些未由-Wall启用的额外警告标志
			 -l参数和-L参数 这是关于链接库的参数
			 		-l紧接着就是库名（去掉lib和.so后缀）
			 		-L紧接着是库文件所在的目录  
* 第五行参数  

		SOURCE=$(wildcard ./src/*.c)		 		

	找出src目录下所有的.c文件。wildcard函数的具体用法参考本工程下学习Makefile笔记   

* 第六行参数  

		OBJECTS=$(patsubst %.c,%.o,$(SOURCES))  
		函数用法参考本工程下学习Makefile笔记 