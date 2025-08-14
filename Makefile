# 2025-08-08学习成果试验：静态模式、include以及嵌套make
# 2025-08-12学习成果：自动生成依赖

cflags_common := -Wall -Wextra

CFLAGS := $(cflags_common) -g -O0

target := startup_debug

bitree_src := src/bitree
bitree_sources:=$(wildcard $(bitree_src)/*.c)
# 把src/bitree目录下的.c文件名全替换为.o文件名，然后赋予变量bitree_objects
bitree_objects:=$(bitree_sources:$(bitree_src)/%.c=$(bitree_src)/%.o)

# 执行make默认是debug模式，要发布release版本，请执行make release
debug : $(target)
	@echo "compile completed in DEBUG mode"

$(target) : $(bitree_objects) make_src
	@echo "start linking"
	gcc $(CFLAGS) -o $(target) src/*.o src/stack/obj/*.o src/queue/obj/*.o src/bitree/*.o

make_src:
	make -C src

release: CFLAGS = $(cflags_common) -O2
release: target = startup
release: $(target)
	@echo "compile completed in RELEASE mode"

# 体验include的效果
include src/bitree/Makefile_bitree

.PHONY : all make_src debug clean
clean : clean_bitree
	rm -rf *.exe
	make -C src clean

export cflags_common
export CFLAGS
