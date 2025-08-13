sources:=$(wildcard *.c)
dependencies:=$(sources:%.c=%.d)
# 把目录下的.c文件名全替换为.o文件名，然后赋予变量objects
objects:=$(sources:%.c=%.o)

# -MM表示输出.o文件依赖的.h文件和对应的.c文件
CPARAM:= -MM

compile : $(objects)
	@echo "compile: $(objects)"
	make -C stack
	make -C queue

$(dependencies) : %.d : %.c
	rm -rf $@;\
	gcc $(CPARAM) $< > $@.$$$$;\
	sed 's,\($*\).o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
	rm -rf $@.$$$$
	
# 环境变量MAKECMDGOALS会存放你所指定的终极目标的列表，如果在命令行上，你没有指定目标，那么，这个变量是空值
# 执行make时，MAKECMDGOALS的值为空；执行make clean时，MAKECMDGOALS的值为clean
ifneq ($(MAKECMDGOALS), clean)
include $(dependencies)
endif

.PHONY : compile clean
clean:
	rm -rf *.o *.d
	make -C stack clean
	make -C queue clean