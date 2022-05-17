---
title: USB HUB的驱动
categorite: Linux内核驱动  
---  
1.升级5.3内核以后，板子不支持热插拔了。所以调试一下USB驱动  


# USB3503A USB HUB驱动  
根据核心板原理图可知。usb hub所用芯片为USB3503A,从网上下载下来此芯片的手册。如下
[点此下载]（/download/3503.pdf）  
查看linux是否支持了此驱动：find ./ -name "*3503*" 输出如下  

    ./include/config/usb/hsic/usb3503.h
    ./include/linux/platform_data/usb3503.h
    ./drivers/usb/misc/.usb3503.o.cmd
    ./drivers/usb/misc/usb3503.o
    ./drivers/usb/misc/usb3503.c
    ./Documentation/devicetree/bindings/usb/usb3503.txt 
可知linux中已经支持了驱动，但是是3503的驱动，3503A是否能用？  
#### 分析usb3503.c驱动  
虽然内核支持了usb3503的驱动，但是分析一下也可以对驱动框架多一些了解  



 