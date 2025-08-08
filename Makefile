# 2025-08-08学习成果试验：静态模式、include以及嵌套make

export obj_dir := obj

bitree_src := src/bitree
bitree_sources:=$(wildcard $(bitree_src)/*.c)
# 把src/bitree目录下的.c文件名全替换为.o文件名，然后赋予变量bitree_objects
bitree_objects:=$(bitree_sources:$(bitree_src)/%.c=$(bitree_src)/%.o)

startup : $(bitree_objects) make_src
	@echo "starting link"
	gcc -o startup src/*.o src/stack/*.o src/queue/*.o src/bitree/*.o

make_src:
	make -C src

# 体验include的效果
include src/bitree/Makefile_bitree

.PHONY : clean
clean : clean_bitree
	rm -rf startup.*
	make -C src clean