# Makefile 的基本语法  
指定交叉编译的库以及头文件的方法  
#### Makefile的规则 

    target ... : prerequisites ...
    command
    target ... : prerequisites ...
    command
    target ... : prerequisites ...
    command
    ...
    ...  
#### Makefile中使用变量  
将Makefile中的变量理解成C语言宏,调用这个变量的方法为  “$(变量名)”  
**Demo**  

    edit : main.o kbd.o command.o display.o /
    insert.o search.o files.o utils.o
    cc -o edit main.o kbd.o command.o display.o /
    insert.o search.o files.o utils.o
    main.o : main.c defs.h
    cc -c main.c
    kbd.o : kbd.c defs.h command.h
    cc -c kbd.c
    command.o : command.c defs.h command.h
    cc -c command.c
    display.o : display.c defs.h buffer.h
    cc -c display.c
    insert.o : insert.c defs.h buffer.h
    cc -c insert.c
    search.o : search.c defs.h buffer.h
    cc -c search.c
    files.o : files.c defs.h buffer.h command.h
    cc -c files.c
    utils.o : utils.c defs.h
    cc -c utils.c
    clean :
    rm edit main.o kbd.o command.o display.o /
    insert.o search.o files.o utils.o  
**使用变量之后**  

    objects = main.o kbd.o command.o display.o /
    insert.o search.o files.o utils.o
    edit : $(objects) //在这里使用了变量
    cc -o edit $(objects)
    main.o : main.c defs.h
    cc -c main.c
    kbd.o : kbd.c defs.h command.h
    cc -c kbd.c
    command.o : command.c defs.h command.h
    cc -c command.c
    display.o : display.c defs.h buffer.h
    cc -c display.c
    insert.o : insert.c defs.h buffer.h
    cc -c insert.c
    search.o : search.c defs.h buffer.h
    cc -c search.c
    files.o : files.c defs.h buffer.h command.h
    cc -c files.c
    utils.o : utils.c defs.h
    cc -c utils.c
    clean :
    rm edit $(objects)  

#### 让Makefile主动推导  
仅仅要make看到一个[.o]文件，它就会自己主动的把[.c]文件加在依赖关系中，假设make找到一个whatever.o，那么whatever.c，就会是whatever.o的依赖文件。而且 cc -c whatever.c 也会被推导出来，于是，我们的makefile再也不用写得这么复杂。  
    
    objects = main.o kbd.o command.o display.o /
              insert.o search.o files.o utils.o

    edit : $(objects)
            cc -o edit $(objects)

    main.o : defs.h
    kbd.o : defs.h command.h
    command.o : defs.h command.h
    display.o : defs.h buffer.h
    insert.o : defs.h buffer.h
    search.o : defs.h buffer.h
    files.o : defs.h buffer.h command.h
    utils.o : defs.h

    .PHONY : clean
    clean :
            rm edit $(objects)  
            
#### 清空目标文件夹  
make clean  

    clean:
            rm edit $(objects)  

更好的方法是  

    .PHONY : clean
        clean :
                -rm edit $(objects)  
.PHONY意思表示clean是一个“伪目标”，。而在rm命令前面加了一个小减号的意思就是，也许某些文件出现问题，但不要管，继续做后面的事。当然，clean的规则不要放在文件的开头，不然，这就会变成make的默认目标，相信谁也不愿意这样。不成文的规矩是——“clean从来都是放在文件的最后”。

# Makefile的高级操作  

#### 引用其他的Makefile  
在Makefile使用include关键字可以把别的Makefile包含进来  语法是  

    include <filename>  //filename可以是当前操作系统Shell的文件模式（可以保含路径和通配符）  
    在include前面可以有一些空字符，但是绝不能是[Tab]键开始。include和<filename>可以用一个或多个空格隔开 
    make命令开始时，会把找寻include所指出的其它Makefile，并把其内容安置在当前的位置  

# 书写规则
第一条规则中的目标将被确立为最终的目标。如果第一条规则中的目标有很多个，那么，第一个目标会成为最终的目标。make所完成的也就是这个目标   
#### 规则的语法  

    targets : prerequisites
        command
        ...  

targets是文件名，以空格分开，可以使用通配符。一般来说，我们的目标基本上是一个文件，但也有可能是多个文件。command 是命令行  
#### 在规则中使用通配符  
make支持三各通配符  

    

