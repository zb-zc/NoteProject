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
make支持三个通配符  “*” “？” “[...]”    
#### 文件搜寻  
**当make需要去找寻文件的依赖关系时，你可以在文件前加上路径，但最好的方法是把一个路径告诉make，让make在自动去找。**  
1. Makefile文件中的特殊变量**“VPATH”**就是完成这个功能的，如果没有指明这个变量，make只会在当前的目录中去找寻依赖文件和目标文件。如果定义了这个 **变量**，那么，make就会在当当前目录找不到的情况下，到所指定的目录中去找寻文件了。  
例如 

        VPATH = src:../headers  
        上面的的定义指定两个目录，“src”和“../headers”，make会按照这个顺序进行搜索。目录由“冒号”分隔。当前目录优先级最高  
2. “vpath” 关键字  
    它更为灵活。它可以指定不同的文件在不同的搜索目录中。这是一个很灵活的功能。它的使用方法有三种

    *   
            vpath <pattern> <directories>

    为符合模式<pattern>的文件指定搜索目录<directories>  
    *
            vpath <pattern>

    清除符合模式<pattern>的文件的搜索目录。  
    * vpath

    清除所有已被设置好了的文件搜索目录。  
    
vapth使用方法中的<pattern>需要包含“%”字符。“%”的意思是匹配零或若干字符，例如，“%.h”表示所有以“.h”结尾的文件。<pattern>指定了要搜索的文件集，而<directories>则指定了<pattern>的文件集的搜索的目录。例如   

     vpath %.h ../headers  //要求make在“../headers”目录下搜索所有以“.h”结尾的文件（如果文件没有在当前文件目录下被找到） 
#### 伪目标  
“伪目标”并不是一个文件，只是一个标签，由于“伪目标”不是文件，所以make无法生成它的依赖关系和决定它是否要执行。我们只有通过显示地指明这个“目标”才能让其生效。**“.PHONY”来显示地指明一个目标是“伪目标”**  

    .PHONY: clean
    clean:
            rm *.o temp

#### Makefile的多目标  
Makefile的规则中的目标可以不止一个，其支持多目标，有可能我们的多个目标同时依赖于一个文件，并且其生成的命令大体类似。于是我们就能把其合并起来。  
例如  

    bigoutput littleoutput : text.g
            generate text.g -$(subst output,,$@) > $@  
上述规则等价于：   

        bigoutput : text.g
            generate text.g -big > bigoutput
        littleoutput : text.g
            generate text.g -little > littleoutput

**注意上述使用了一个自动化变量** “$@”   
-$(subst output,,$@) 这是一个函数  

#### 静态模式
静态模式可以更加容易地定义多目标的规则，可以让我们的规则变得更加的有弹性和灵活  
语法如下  
        
        <targets ...>: <target-pattern>: <prereq-patterns ...>
            <commands>  
        targets定义了一系列的目标文件，可以有通配符。是目标的一个集合。

    target-parrtern是指明了targets的模式，也就是的目标集模式。

    prereq-parrterns是目标的依赖模式，它对target-parrtern形成的模式再进行一次依赖 
    
**第一次看我也不懂这个说的是什么，还是看例子吧**  
* 如果我们把<target-parrtern>定义成“%.o”，意思就是 ： 我们<target>集合中都是以.o结尾的。  
* 而如果我们的<prereq-parrterns>定义成“%.c”，意思是对<target-parrtern>所形成的目标集进行二次定义，其计算方法是，取<target-parrtern>模式中的“%”（也就是去掉了[.o]这个结尾），并为其加上[.c]这个结尾，形成的新集合。  

**实例如下**   


    objects = foo.o bar.o

    all: $(objects)

    $(objects): %.o: %.c  //这里是为了挑拣出foo.c和bar.c 作为上一步的依赖
            $(CC) -c $(CFLAGS) $< -o $@

上述例子中 指明了我们的目标从$object中获取，“%.o”表明要所有以“.o”结尾的目标，也就是“foo.o bar.o”，也就是变量$object集合的模式，而依赖模式“%.c”则取模式“%.o”的“%”，也就是“foo bar”，并为其加下“.c”的后缀，于是，我们的依赖目标就是“foo.c bar.c”  

而命令中的 **“$<”** 和 **“$@”** 则是自动化变量，“$<”表示所有的依赖目标集（也就是“foo.c bar.c”），“$@”表示目标集（也就是“foo.o bar.o”）   
#### 自动生成依赖性  
在Makefile中，我们的依赖关系可能会需要包含一系列的头文件，比如，如果我们的main.c中有一句“#include "defs.h"”，那么我们的依赖关系应该是： 

    main.o : main.c defs.h  

但是，如果是一个比较大型的工程，你必需清楚哪些C文件包含了哪些头文件，并且，你在加入或删除头文件时，也需要小心地修改Makefile，这是一个很没有维护性的工作。为了避免这种繁重而又容易出错的事情，我们可以使用C/C++编译的一个功能。大多数的C/C++编译器都支持一个“-M”的选项，即自动找寻源文件中包含的头文件，并生成一个依赖关系。例如，如果我们执行下面的命令：  

        cc -M main.c  
其输出是  

        main.o : main.c defs.h  
是由编译器自动生成的依赖关系，这样一来，你就不必再手动书写若干文件的依赖关系，而由编译器自动生成了。需要提醒一句的是，如果你使用GNU的C/C++编译器，你得用“-MM”参数  

**这一部分不是很懂留到之后研究**  


# 书写命令  
#### 显示命令  
通常，make会把其要执行的命令行在命令执行前输出到屏幕上。当我们用“@”字符在命令行前，那么，这个命令将不被make显示出来   
带入make参数“-n”或“--just-print”，那么其只是显示命令，但不会执行命令  
#### 命令执行  
 当依赖目标新于目标时，也就是当规则的目标需要被更新时，make会一条一条的执行其后的命令  
 **如果你要让上一条命令的结果应用在下一条命令时，你应该使用分号分隔这两条命令**  
#### 嵌套执行make  
语法如下  

    subsystem:
            cd subdir && $(MAKE)  
其等价于  

    subsystem:
            $(MAKE) -C subdir  
* 这两个例子的意思都是先进入“subdir”目录，然后执行make命令.我们把这个叫做总控Makefile,总控Makefile的变量可以传递到下级的Makefile中（如果你显示的声明），但是不会覆盖下层的Makefile中所定义的变量，除非指定了“-e”参数。  
* 需要注意的是，有两个变量，一个是 **SHELL** ，一个是 **MAKEFLAGS** ，这两个变量不管你是否export，其总是要传递到下层Makefile中，这是一个系统级的环境变量.  
* 还有一个在“嵌套执行”中比较有用的参数，“-w”或是“--print-directory”会在make的过程中输出一些信息，让你看到目前的工作目录。  
# 使用变量  
#### 变量的基础  
定义变量的初值时用“=”。    
“:=”  前面的变量不能使用后面的变量，只能使用前面已定义好了的变.      
“？=” 其含义是，如果变量没有被定义过，那么变量的值就是“bar”，如果变量先前被定义过，那么这条语将什么也不做。  
“+=” 追加变量的值  


#####  变量的高级用法    
1. 变量值的替换  
    可以代替变量中的共有部分，格式是“$(var:a=b)”或是“${var:a=b}”，把变量“var”中所有以“a”字串“结尾”的“a”替换成“b”字串。
**实例**  


    foo := a.o b.o c.o
    bar := $(foo:.o=.c)  
    把foo变量中.o结尾的都换成.c结尾的。所以$(bar)的值就是“a.c b.c c.c”  
    
**另外一种变量替换的方法是静态模式**  
**还有一个替换函数，这个函数有三个参数，第一个参数是被替换字符，第二个参数是替换字符，第三个参数是替换操作作用的字串** 实例如下所示  

    $(subst <aa>,<bb>,<text>)
    把text中的aa替换成bb  
    
        
2. 把变量的值再当变量  


    x = y
    y = z
    a := $($(x))  
    
# 使用条件判断  
#### 语法  
* ifeq (<arg1>, <arg2>)   else 比较参数“arg1”和“arg2”的值是否相同  
* ifneq (<arg1>, <arg2>) else  比较参数“arg1”和“arg2”的值是否相同，如果不同，则为真。  
* ifdef <variable-name>  else 如果变量<variable-name>的值非空，那到表达式为真  
* ifndef <variable-name> else 如果变量<variable-name>的值非空，那到表达式为假  

# 使用函数  
#### 函数的调用  

     $(<function> <arguments>)  
     //<function>就是函数名，make支持的函数不多。<arguments>是函数的参数，参数间以逗号“,”分隔
#### 字符串处理函数  
**字符串替换函数——subst**  

    $(subst <from>,<to>,<text>) //上面笔记记录郭这个函数  
**模式字符串替换函数——patsubst** 

    $(patsubst <pattern>,<replacement>,<text>)
    
查找<text>中的单词（单词以“空格”、“Tab”或“回车”“换行”分隔）是否符合模式<pattern>如果匹配的话，则以<replacement>替换。例如  

    $(patsubst %.c,%.o,x.c.c bar.c)  
    //把字串“x.c.c bar.c”符合模式[%.c]的单词替换成[%.o]，返回结果是“x.c.o bar.o”

和静态模式相似，不过这个函数用处更广  
**去空格函数——strip**  

    $(strip <string>)  
    
去掉<string>字串中开头和结尾的空字符  

**查找字符串函数——findstring**  

    $(findstring <find>,<in>)  
    
在字串<in>中查找<find>字串

**过滤函数——filter**  

    $(filter <pattern...>,<text>)  
    
以<pattern>模式过滤<text>字符串中的单词，保留符合模式<pattern>的单词。可以有多个模式。  

**反过滤函数——filter-out**  

    $(filter-out <pattern...>,<text>)  
    
以<pattern>模式过滤<text>字符串中的单词，去除符合模式<pattern>的单词。可以有多个模式  

# 规范 

    “all”
        这个伪目标是所有目标的目标，其功能一般是编译所有的目标。
     “clean”
        这个伪目标功能是删除所有被make创建的文件。
     “install”
        这个伪目标功能是安装已编译好的程序，其实就是把目标执行文件拷贝到指定的目标中去。
     “print”
        这个伪目标的功能是例出改变过的源文件。
     “tar”
        这个伪目标功能是把源程序打包备份。也就是一个tar文件。
     “dist”
        这个伪目标功能是创建一个压缩文件，一般是把tar文件压成Z文件。或是gz文件。
     “TAGS”
        这个伪目标功能是更新所有的目标，以备完整地重编译使用。
     “check”和“test”
        这两个伪目标一般用来测试makefile的流程。



# 隐含规则  
#### 使用隐含规则  
make会在自己的“隐含规则”库中寻找可以用的规则，如果找到，那么就会使用。如果找不到，那么就会报错  

    foo : foo.o bar.o
            cc –o foo foo.o bar.o $(CFLAGS) $(LDFLAGS)  
我们可以注意到，这个Makefile中并没有写下如何生成foo.o和bar.o这两目标的规则和命令。因为make的“隐含规则”功能会自动为我们自动去推导这两个目标的依赖目标和生成命令。   
**上面例子的本来面目是**  

    foo.o : foo.c
            cc –c foo.c $(CFLAGS)
    bar.o : bar.c
        cc –c bar.c $(CFLAGS)  
        
**make调用的隐含规则是，把[.o]的目标的依赖文件置成[.c]，并使用C的编译命令“cc –c $(CFLAGS) [.c]”来生成[.o]的目标**   
* 如果我们为[.o]文件书写了自己的规则，那么make就不会自动推导并调用隐含规则，它会按照我们写好的规则忠实地执行  
* 还有，在make的“隐含规则库”中，每一条隐含规则都在库中有其顺序，越靠前的则是越被经常使用的，所以，这会导致我们有些时候即使我们显示地指定了目标依赖，make也不会管。如下  


    foo.o : foo.p

    如果目录下存在了“foo.c”文件，那么我们的隐含规则一样会生效，并会通过“foo.c”调用C的编译器生成foo.o文件  
    
#### 隐含规则总结  
**编译C程序的隐含规则**  
“<n>.o”的目标的依赖目标会自动推导为“<n>.c”，并且其生成命令是“$(CC) –c $(CPPFLAGS) $(CFLAGS)”  
**编译C++程序的隐含规则**  
“<n>.o”的目标的依赖目标会自动推导为“<n>.cc”或是“<n>.C”，并且其生成命令是“$(CXX) –c $(CPPFLAGS) $(CFLAGS)”  

#### 隐含规则使用的变量  
第一条隐含规则——编译C程序的隐含规则的命令  


    $(CC) –c $(CFLAGS) $(CPPFLAGS)    
    //如果你把变量“$(CC)”重定义成“gcc”，把变量“$(CFLAGS)”重定义成“-g”，那么，隐含规则中的命令全部会以“gcc –c -g $(CPPFLAGS)”的样子来执行了。  
**我们可以把隐含规则中使用的变量分成两种：一种是命令相关的，如“CC”；一种是参数相的关，如“CFLAGS”。** 记录一下重要的常用的 
1. 关于命令的变量。  

* CC  


        C语言编译程序。默认命令是“cc”  

* CXX   


        C++语言编译程序。默认命令是“g++”
    
2. 关于命令参数的变量 
* CFLAGS  
    
        C语言编译器参数   
* CPPFLAGS  

        C预处理器参数  
# 自动化变量  (常用的见过的)

* $@  

    表示规则中的目标文件集。在模式规则中，如果有多个目标，那么，"$@"就是匹配于目标中模式定义的集合  
* $%   
    不太懂  
* $<    
     依赖目标中的第一个目标名字。如果依赖目标是以模式（即"%"）定义的，那么"$<"将是符合模式的一系列的文件集。注意，其是一个一个取出来的。  
* $?  
    所有比目标新的依赖目标的集合。以空格分隔。  

* $^  
    所有的依赖目标的集合  

# Makefile 中函数库文件操作  



        
    



    

     


    

