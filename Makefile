include_dir=./include
include_stack=./include/stack
include_queue=./include/queue
include_bitree=./include/bitree

src_dir=./src
src_stack=./src/stack
src_queue=./src/queue
src_bitree=./src/bitree

obj_dir=obj

header_prerequisites=$(include_dir)/SqList.h $(include_dir)/ForwardList.h $(include_dir)/String.h $(include_stack)/Stack.h $(include_stack)/StackImpl2.h \
$(include_stack)/SharedStack.h $(include_queue)/Queue.h $(include_queue)/QueueImpl2.h $(include_queue)/QueueImpl3.h $(include_queue)/LinkQueue.h \
$(include_queue)/ReusableLinkQueue.h $(include_bitree)/BiTree.h $(include_bitree)/BiTree.h

obj_prerequisites=$(obj_dir)/SqList.o $(obj_dir)/ForwardList.o $(obj_dir)/String.o $(obj_dir)/Stack.o $(obj_dir)/StackImpl2.o $(obj_dir)/SharedStack.o $(obj_dir)/Queue.o \
$(obj_dir)/QueueImpl2.o $(obj_dir)/QueueImpl3.o $(obj_dir)/LinkQueue.o $(obj_dir)/ReusableLinkQueue.o $(obj_dir)/BiTree.o $(obj_dir)/BstTree.o $(obj_dir)/Startup.o


startup : $(obj_prerequisites)
# 链接，生成可执行文件
	gcc -o startup $(obj_prerequisites)

$(obj_dir)/SqList.o : $(include_dir)/SqList.h $(src_dir)/SqList.c
	gcc -c $(src_dir)/SqList.c
$(obj_dir)/ForwardList.o : $(include_dir)/ForwardList.h
	gcc -c $(src_dir)/ForwardList.c
$(obj_dir)/String.o : $(include_dir)/String.h
	gcc -c $(src_dir)/String.c
	
$(obj_dir)/Stack.o : $(include_stack)/Stack.h $(include_bitree)/BiTree.h
	gcc -c $(src_stack)/Stack.c
$(obj_dir)/StackImpl2.o : $(include_stack)/StackImpl2.h
	gcc -c $(src_stack)/StackImpl2.c
$(obj_dir)/SharedStack.o : $(include_stack)/SharedStack.h
	gcc -c $(src_stack)/SharedStack.c

$(obj_dir)/Queue.o : $(include_queue)/Queue.h
	gcc -c $(src_queue)/Queue.c
$(obj_dir)/QueueImpl2.o : $(include_queue)/QueueImpl2.h
	gcc -c $(src_queue)/QueueImpl2.c
$(obj_dir)/QueueImpl3.o : $(include_queue)/QueueImpl3.h
	gcc -c $(src_queue)/QueueImpl3.c
$(obj_dir)/LinkQueue.o : $(include_queue)/LinkQueue.h
	gcc -c $(src_queue)/LinkQueue.c
$(obj_dir)/ReusableLinkQueue.o : $(include_queue)/ReusableLinkQueue.h $(include_bitree)/BiTree.h
	gcc -c $(src_queue)/ReusableLinkQueue.c
	
$(obj_dir)/BiTree.o : $(include_bitree)/BiTree.h $(include_stack)/Stack.h $(include_queue)/ReusableLinkQueue.h
	gcc -c $(src_dir)/bitree/BiTree.c
$(obj_dir)/BstTree.o : $(include_bitree)/BiTree.h $(include_bitree)/BstTree.h
	gcc -c $(src_bitree)/BstTree.c
	
$(obj_dir)/Startup.o : $(header_prerequisites)
# 创建存放目标文件的目录
	-cmd /c mkdir $(obj_dir)
	gcc -c $(src_dir)/Startup.c
	mv *.o $(obj_dir)/
	
.PHONE : clean
clean:
	rm -rf $(obj_dir)/* startup.exe
# 删除目标文件目录
	-cmd /c rd /s /q $(obj_dir)