sources:=$(wildcard *.c)
dependencies:=$(sources:%.c=%.d)
# 把目录下的.c文件名全替换为.o文件名，然后赋予变量objects
objects:=$(sources:%.c=%.o)

# -MM表示输出.o文件依赖的.h文件和对应的.c文件
CPARAM:= -MM

.PHONY : clean

compile : $(objects)
	@echo "Building: $(objects)"
	
$(dependencies) : %.d : %.c
	rm -rf $@;\
	gcc $(CPARAM) $< > $@;\
	echo "	gcc -c $< -o $*.o" >> $@

include $(dependencies)

clean:
	rm -rf *.d *.o