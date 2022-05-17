---
title: uboot 基础  
---

**芯片启动流程**
![image](https://github.com/zb-zc/PictureWareHouse/blob/main/UBOOT.png?raw=true)

**芯片启动方式**  
通过设置OM来进行选择芯片从哪里启动 
**Android_Exynos4412_iROM_Secure_Booting_Guide_Ver.1.00.00.pdf** OM寄存器 
![image](https://github.com/zb-zc/PictureWareHouse/blob/main/OM_2022-05-02%20023708.png?raw=true)  
1. 以TF卡启动方式为例
	* 首先查看底板datasheet 中的TF模块如下
	![image](https://github.com/zb-zc/PictureWareHouse/blob/main/TF%20030054.png?raw=true)
	由OM寄存器可知，由tf卡启动时对应的管脚是SDMMC_CH2，OM寄存器的值为00010  
	查看datasheet管脚定义如下
	![image](https://github.com/zb-zc/PictureWareHouse/blob/main/datasheet%E7%AE%A1%E8%84%9A%E5%AE%9A%E4%B9%89034029.png?raw=true)  
	如图所示 Pin name为Xmmc2DATA2，继续搜索Xmmc2DATA2可知，链接到了如下  
	![image](https://github.com/zb-zc/PictureWareHouse/blob/main/%E6%9D%BF%E5%AF%B9%E6%9D%BF%E8%BF%9E%E6%8E%A5%E5%99%A82022-05-02%20030928.png?raw=true)  
	* OM寄存器为bit[0-5] 查看底板原理图中如下  
	![image](https://github.com/zb-zc/PictureWareHouse/blob/main/OM%E9%80%89%E6%8B%A9%20035426.png?raw=true)  
	核心板中OM的链接如下  
	![image](https://github.com/zb-zc/PictureWareHouse/blob/main/om_coare035943.png?raw=true)  
	由此可知 OM寄存器的初试状态为 XOM1=0;XOM2=0；XOM3=1;XOM4=0;XOM5=1;XOM6=0;  
	当选择tf卡启动时OM寄存器需要被设置为00010.所以XOM2需要设置为1；  
	但是实际原理图中默认XOM3=XOM5=1,OM寄存器的值为10100.所以默认是由eMMC44_CH4启动

**uboot源码结构** 

![image](https://github.com/zb-zc/PictureWareHouse/blob/main/Uboot_code.png?raw=true) 

4. Build_Uboot.sh  
4行：if[ -z $1]//判断第一个参数是空  
		
		shell脚本语法：
		1. if语句  
			if [ command ]; then
     			符合该条件执行的语句
			fi 
		2. if扩展  
			if [ command ];then
     			符合该条件执行的语句
			elif [ command ];then
     			符合该条件执行的语句
			else
     			符合该条件执行的语句
			fi 
		3. -z 判断 变量的值，是否为空 
		4. $1 位置参数，$1 是第一个参数  
12-19行： 配置参数  
32行：CPU核数  
33行：当前目录  
45-91行：根据第一个参数生成不同的uboot；在此调用Uboot的Makefile   
93行：make -j4 多核编译   

**17. Makefile文件**  
Makefile 中的几千行对与不同平台正真有用的只有几百行，所以对于Itop平台来说从3244行开始  

	
		itop_4412_android_config_scp_1GDDR:		unconfig
		@$(MKCONFIG) $(@:_config=) arm arm_cortexa9 smdkc210 samsung s5pc210 SCP_1GDDR

MKCONFIG：111行：MKCONFIG	:= $(SRCTREE)/mkconfig  
SRCTREE：当前所在目录；  
$(@:_config=) : @表示目标文件集 @:_config= 就是将目标集中的_config字符换成空  

		mkconfig itop_4412_android arm arm_cortexa9 smdkc210 samsung s5pc210 SCP_1GDDR

**mkconfig文件**  
	
		mkconfig itop_4412_android arm arm_cortexa9 smdkc210 samsung s5pc210 SCP_1GDDR	
 		

		17-28: 根据参数7选择board   


**精简后的Makefile**  

	24-34行 ：版本相关等
	36-44行 运行一下
			HOSTARCH=x86_64 主机的平台
	45-46行
			HOSTOS= linux 主机的操作系统
	48-51行
			SHELL=/bin/bash
	53行
			设置环境变量参数 HOSTARCH HOSTOS SHELL
	56行
			定义一个变量VENDOR
	59-64行
			Allow for silent builds 允许编译的时候不打印信息
	88-92行
			编译的时候输入参数
	94-95行
			设置saved-output等于当前目录
	97-109行
			设置环境变量 TOPDIR SRCTREE OBJTREE
	111行				  	
			MKCONFIG设置为当前目录下的mkconfig
	114-117行
			设置环境变量REMOTE_BUILD
	122-129行
			设置环境变量obj src
	127行
			不用管
	137-140行
			不用管
	145-147行
			取出预编译的宏
			关键词：include/autoconf.mk
	150-151行
			环境变量ARCH CPU BOARD VENDOR SOC
	152-200行
			配置编译器
	203行
		include $(TOPDIR)/config.mk gcc-xx xx.x xxx.xx …… -I include<libxx.a> -o xxx这里才是真正的Makefile文件。
	205行
		start必须先运行
	221-325行
		包含的各种库
	
	331行
		ALL+=$(obj)u-boot.srec $(obj)u-boot.bin $(obj)System.map $(U_BOOT_NAND) $(U_BOOT_ONENAND) 332-
	需要u-boot.bin
	u-boot.bin（二进制文件）依赖u-boot（elf文件）
	u-boot
	GEN_UBOOT:
	UNDEF_SYM=`$(OBJDUMP) -x $(LIBBOARD) $(LIBS) | \
                sed  -n -e 's/.*\($(SYM_PREFIX)__u_boot_cmd_.*\)/-u\1/p'|sort|uniq`;\
                cd $(LNDIR) && $(LD) $(LDFLAGS) $$UNDEF_SYM $(__OBJS) \
                        --start-group $(__LIBS) --end-group $(PLATFORM_LIBS) \
                        -Map u-boot.map -o u-boot
	u-boot:	depend $(SUBDIRS) $(OBJS) $(LIBBOARD) $(LIBS) $(LDSCRIPT) $(obj)u-boot.lds
                $(GEN_UBOOT) -O

	u-boot.map	:预编译的文件
	

	UNDEF_SYM=`gcc-xx -x lib*.a  ;
	gcc-xx -Bstatic -T u-boot.lds  -Ttext 0xc3e00000 $UNDEF_SYM cpu/arm_cortexa9/start.o --start-group lib*.a  --end-group  -lgcc -Map u-boot.map -o u-boot

## uboot 启动分析
第一个执行的文件是cpu/arm_cortexa9/start.S （.s文件是汇编语言）
每一种芯片都有它的汇编指令  

		57-65:中断向量 
			.globl _start： .global关键字用来让一个符号对链接器可见，可以供其他链接对象模块使用。 .global _start 让_start符号成为可见的标示符，这样链接器就知道跳转到程序中的什么地方并开始执行
			_start: b	reset 在arm中 b是跳转指令;跳转reset 
		240-243:/* Read booting information */ 读取OM的状态
			ldr	r0, =POWER_BASE  //这里是伪指令dr汇编指令和ldr伪汇编指令的区别：ldr汇编指令没有 “=”，ldr伪汇编指令有 “=”
						#define POWER_BASE   0X10020000
						查datasheet可得0X10020000为Base Address,且偏移量为0的寄存器OM_STAT（OM status register）
        	ldr	r1, [r0,#OMR_OFFSET]
        	bic	r2, r1, #0xffffffc1

