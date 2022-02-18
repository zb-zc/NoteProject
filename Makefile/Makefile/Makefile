CFLAGS = -g -O2 -Wall -Wextra -Isrc -rdynamic
LIBS = 
CC := gcc

SOURCES = $(wildcard ./src/*.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

TEST_SRC = $(wildcard tests/*_tests.c)
TESTS = $(patsubst %.c,%.o,$(TEST_SRC))
TARGET = ./bin/Hello  
$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) 
	
.PHONY : clean
clean :
		rm ./bin/Hello $(object)

.PHONY : install 

.PHONY : print  

.PHONY : tar 


