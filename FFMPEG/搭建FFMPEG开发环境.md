# 搭建FFMPEG的开发环境
搭建开发环境其实就是通过一个Makefile 来引用ffmpeg的库，从而完成编译  
```
BUILD_TOOL = aarch64-himix100-linux-
DEFINC = -I"/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg_build/include" -I"/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg/" -I"/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg/libavutil/" -I"/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg/libavcodec" -I"/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg/libavdevice" -I"/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg/libavfilter" -I"/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg/libavformat" -I"/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg/libavresample" -I"/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg/libpostproc" -I"/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg/libswresample" -I"/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg/libswscale" -I"/home/xxx/work/x264/build/include" -I"/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg_build_1/include"
CC = $(BUILD_TOOL)g++

#CPP = $(BUILD_TOOL)g++

LIB = -L/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg_build_1/lib -lavcodec  -L/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg_build_1/lib -lavdevice  -L/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg_build_1/lib -lavfilter  -L/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg_build_1/lib -lavformat  -L/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg_build_1/lib -lavutil  -L/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg_build_1/lib -lpostproc  -L/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg_build_1/lib -lswresample -L/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg_build_1/lib -lswscale -L/home/xxx/work/x264/build/lib -lx264
#CSRC :=  $(wildcard /home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg/libavutil/opt.c) $(wildcard /home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg/libavutil/utils.c) $(wildcard /home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg/libavcodec/allcodecs.c)
#COBJS := $(patsubst %.c,%.o,$(CSRC))

CPPOBJS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET = $(basename $(CPPOBJS))
$(TARGET): $(CPPOBJS)
	$(CC) -o $(TARGET) $(wildcard *.cpp) $(DEFINC) $(LIB)
$(CPPOBJS): $(wildcard *.cpp) 
	$(CC) -c $^ -o $@ $(DEFINC) $(LIB)

#	$(CPP) -o $(TARGET) $^ $(DEFINC) $(LIB)
	
.PHONT: clean
clean:
	-rm *.o
	-rm $(TARGET)

```
## **编译静态库**

如果要将自己开发的ffmpeg程序方法嵌入式设备上运行，需要借助静态库。在ffmpeg源码中通过配置config来编译出静态库,下面我将配置命令写成一个脚本来运行。
```
#!/bin/bash
./configure \
--prefix=/home/ubuntu/ZhaoBo/FFmpeg/code/ffmpeg_build_1 \
--enable-static \
--enable-shared \
--disable-debug \
--disable-asm \
--disable-ffplay \
--disable-ffprobe \
--enable-small \
--disable-doc \
--enable-demuxer=rtsp \
--enable-parser=h264 \
--enable-cross-compile \
--enable-libx264 \
--enable-nonfree \
--enable-gpl \
--disable-programs \
--arch=aarch64 \
--target-os=linux \
--cross-prefix=aarch64-himix100-linux- \
--extra-cflags=-I/home/xxx/work/x264/build/include \
--extra-ldflags=-L/home/xxx/work/x264/build/lib 

```