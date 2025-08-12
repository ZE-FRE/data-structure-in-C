sources:=$(wildcard *.c)
dependencies:=$(sources:%.c=%.d)
# 把目录下的.c文件名全替换为.o文件名，然后赋予变量objects
objects:=$(sources:%.c=%.o)

# -MM表示输出.o文件依赖的.h文件和对应的.c文件
CPARAM:= -MM

compile : $(objects)
	@echo "Building: $(objects)"
	make -C stack
	make -C queue

$(dependencies) : %.d : %.c
	rm -rf $@;\
	gcc $(CPARAM) $< > $@.$$$$;\
	sed 's,\($*\).o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
	rm -rf $@.$$$$
	
include $(dependencies)

.PHONY : clean
clean:
	rm -rf *.o *.d
	make -C stack clean
	make -C queue clean