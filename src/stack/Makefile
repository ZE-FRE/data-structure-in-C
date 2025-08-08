sources=$(wildcard *.c)
# 把目录下的.c文件名全替换为.o文件名，然后赋予变量objects
objects:=$(sources:%.c=%.o)

all : $(objects)
	@echo "Building: $(objects)"

$(objects) : %.o : %.c
	gcc -c $< -o $@

.PHONY : clean
clean:
	rm -rf *.o