#include "BiTree.h"
#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "ReusableLinkQueue.h"

BiTree createDefaultBiTree()
{
	BiTree bitree = NULL;
	BiElemType elems[] = { 34,24,18,6,'#',14,'#','#','#',28,27,'#','#',32,'#','#',39,'#',64,42,'#',48,'#','#',66,'#','#' };
	InitBiTree(&bitree, elems, sizeof(elems) / sizeof(elems[0]));
	return bitree;
}

void InitBiTree(BiTree* bitree, BiElemType elems[], int len)
{
	Queue queue;
	InitQueue(&queue);
	for (int i = 0; i < len; ++i)
		EnQueue(&queue, elems[i]);
	InitBiTreeFromQueue(bitree, &queue);
	DestroyQueue(&queue);
}

void InitBiTreeFromQueue(BiTree* bitree, Queue* queue)
{
	BiElemType elem;
	if (!DeQueue(queue, &elem) || elem == PLACE_HOLDER) {
		*bitree = NULL;
		return;
	}
	BiNode* newNode = newBiNode(elem);
	if (!newNode) return;
	*bitree = newNode;
	// 生成左子树
	InitBiTreeFromQueue(&(*bitree)->left, queue);
	// 生成右子树
	InitBiTreeFromQueue(&(*bitree)->right, queue);
}

BiNode* newBiNode(BiElemType elem)
{
	BiNode* node = (BiNode*)malloc(sizeof(BiNode));
	// 空间分配失败
	if (!node) return NULL;
	node->elem = elem;
	node->left = node->right = NULL;
	node->visited = false;
	return node;
}

// 后续遍历二叉树，遍历过程中释放结点内存
void DestroyBiTree(BiTree bitree)
{
	if (bitree == NULL) return;
	// 销毁左子树
	DestroyBiTree(bitree->left);
	// 销毁右子树
	DestroyBiTree(bitree->right);
	// 释放二叉树根结点
	free(bitree);
}

void PreOrderRecur(BiTree bstTree, VisitBiNode visit_func)
{
	if (bstTree == NULL) return;
	visit_func(bstTree);
	PreOrderRecur(bstTree->left, visit_func);
	PreOrderRecur(bstTree->right, visit_func);
}

void InOrderRecur(BiTree bstTree, VisitBiNode visit_func)
{
	if (bstTree == NULL) return;
	InOrderRecur(bstTree->left, visit_func);
	visit_func(bstTree);
	InOrderRecur(bstTree->right, visit_func);
}

void PostOrderRecur(BiTree bstTree, VisitBiNode visit_func)
{
	if (bstTree == NULL) return;
	PostOrderRecur(bstTree->left, visit_func);
	PostOrderRecur(bstTree->right, visit_func);
	visit_func(bstTree);
}

void PreOrder(BiTree bitree, VisitBiNode visit_func)
{
	Stack stack;
	Stack* stack_ptr = &stack;
	InitStack(stack_ptr);
	BiNode* node = bitree;
	while (node || !IsEmpty(stack_ptr)) {
		if (node) { // 当前结点存在，则访问后，遍历左子树
			visit_func(node);
			Push(stack_ptr, node);
			node = node->left;
		}
		else { // 从左子树返回
			Pop(stack_ptr, &node);
			node = node->right;
		}
	}
	DestroyStack(stack_ptr);
}

void InOrder(BiTree bitree, VisitBiNode visit_func)
{
	Stack stack;
	Stack* stack_ptr = &stack;
	InitStack(stack_ptr);
	BiNode* node = bitree;
	while (node || !IsEmpty(stack_ptr)) {
		if (node) { // 当前结点存在，遍历左子树
			Push(stack_ptr, node);
			node = node->left;
		}
		else { // 从左子树返回
			Pop(stack_ptr, &node);
			visit_func(node);
			node = node->right;
		}
	}
	DestroyStack(stack_ptr);
}

void PostOrder(BiTree bitree, VisitBiNode visit_func)
{
	Stack stack;
	InitStack(&stack);
	Stack* stack_ptr = &stack;
	BiNode* node = bitree;
	while (node || !IsEmpty(stack_ptr)) {
		if (node) { // 一直往左走
			Push(stack_ptr, node);
			node = node->left;
		}
		else {
			Peek(stack_ptr, &node);
			if (node->right && !node->right->visited) { // 右子树还未访问，表明是从左子树返回的
				// 遍历右子树
				node = node->right;
			}
			else { // 右子树已访问
				Pop(stack_ptr, &node);
				visit_func(node);
				node->visited = true;
				node = NULL;
			}
		}
	}
	DestroyStack(stack_ptr);
}

void LevelOrder(BiTree bitree, VisitBiNode visit_func)
{
	if (bitree == NULL) return;
	ReusableLinkQueue queue;
	InitReusableQueue(&queue);
	EnReusableQueue(&queue, bitree);
	BiNode* node = NULL;
	while (DeReusableQueue(&queue, &node)) {
		visit_func(node);
		if (node->left)
			EnReusableQueue(&queue, node->left);
		if (node->right)
			EnReusableQueue(&queue, node->right);
	}
	DestroyReusableQueue(&queue);
}

void printBiNode(BiNode* node)
{
	if (node)
		printf("%d ", node->elem);
}

void printBiNodeAsChar(BiNode* node)
{
	if (node)
		printf("%c ", node->elem);
}

void testBiTreeTraverse()
{
	/*
	 * 先序：34,24,18,6,14,28,27,32,39,64,42,48,66
	 * 中序：6,14,18,24,27,28,32,34,39,42,48,64,66
	 * 后序：14,6,18,27,32,28,24,48,42,66,64,39,34
	 * 层序：34,24,39,18,28,64,6,27,32,42,66,14,48
	 */
	BiTree bitree = createDefaultBiTree();
	puts("递归遍历二叉树。");

	printf("先序序列：");
	PreOrderRecur(bitree, printBiNode);
	printf("\n中序序列：");
	InOrderRecur(bitree, printBiNode);
	printf("\n后序序列：");
	PostOrderRecur(bitree, printBiNode);

	printf("\n\n非递归遍历二叉树。\n");
	printf("先序序列：");
	PreOrder(bitree, printBiNode);
	printf("\n中序序列：");
	InOrder(bitree, printBiNode);
	printf("\n后序序列：");
	PostOrder(bitree, printBiNode);

	printf("\n\n层序序列：");
	LevelOrder(bitree, printBiNode);

	DestroyBiTree(bitree);
}

void testBiTree()
{
	//testBiTreeTraverse();

	//testContraryLevelOrder();

	//testBiTreeHeight();

	//testIsCompleteBitree();

	//testDoubleNodeCount();

	//testSwapLeftRight();

	//testKValueOnPreOrder();

	//testDeleteSubTree();

	//testPrintAncestors();

	//testBitreeWidth();

	//testFullBiTreePreToPost();

	//testLinkLeaf();

	//testBitreeSimilarity();

	//testBitreeWPL();

	//testPrintExpression();

	//testSqBiTreeIsBST();

	//testBranchCount();

	//testExchangeLeftRight();

	//testLeafLongestDistance();

	//testIsSubTree();

	testBitreeExpandToList();

}

void contraryLevelOrder(BiTree bitree)
{
	if (bitree == NULL) return;
	Stack stack;
	InitStack(&stack);
	Stack* stack_ptr = &stack;
	ReusableLinkQueue queue;
	InitReusableQueue(&queue);
	EnReusableQueue(&queue, bitree);
	BiNode* node = NULL;
	while (DeReusableQueue(&queue, &node)) {
		// 入栈
		Push(stack_ptr, node);
		if (node->left)
			EnReusableQueue(&queue, node->left);
		if (node->right)
			EnReusableQueue(&queue, node->right);
	}

	// 出栈访问
	while (Pop(stack_ptr, &node)) 
		printf("%d ", node->elem);

	DestroyStack(stack_ptr);
	DestroyReusableQueue(&queue);
}

void testContraryLevelOrder()
{
	puts("王道04：试给出二叉树的自下而上、从右到左的层次遍历算法。");
	BiTree bitree = createDefaultBiTree();
	printf("逆层序遍历序列：");
	contraryLevelOrder(bitree);
	DestroyBiTree(bitree);
}

int bitreeHeight(BiTree bitree)
{
	Stack stack;
	InitStack(&stack);
	Stack *stack_ptr = &stack;
	BiNode *node = bitree;
	int max_height = 0;
	int cur_height = 0;
	// 前一个访问结点
	BiNode* prev_visit = NULL;
	while (node || !IsEmpty(stack_ptr)) {
		if (node) { // 一直向左走
			++cur_height;
			if (cur_height > max_height)
				max_height = cur_height;
			Push(stack_ptr, node);
			node = node->left;
		}
		else {
			Peek(stack_ptr, &node);
			if (node->right && node->right != prev_visit) { // 右子树还未访问，表明是从左子树返回的
				node = node->right;
			}
			else {
				Pop(stack_ptr, &node);
				--cur_height;
				prev_visit = node;
				node = NULL;
			}
		}
	}
	DestroyStack(stack_ptr);
	return max_height;
}

void testBiTreeHeight()
{
	puts("05：假设二叉树采用二叉链表存储结构，设计一个非递归算法求二叉树的高度。");
	BiTree bitree = createDefaultBiTree();
	printf("二叉树高度为：%d", bitreeHeight(bitree));
	DestroyBiTree(bitree);

}

bool isCompleteBitree(BiTree bitree)
{
	ReusableLinkQueue queue;
	InitReusableQueue(&queue);
	EnReusableQueue(&queue, bitree);
	BiNode* node = NULL;
	while (!ReusableQueueEmpty(&queue)) {
		DeReusableQueue(&queue, &node);
		if (node) {
			EnReusableQueue(&queue, node->left);
			EnReusableQueue(&queue, node->right);
		}
		else { // 遍历到第一个空结点
			while (!ReusableQueueEmpty(&queue)) {
				DeReusableQueue(&queue, &node);
				if (node)
					return false;
			}
		}
	}
	return true;
}

void testIsCompleteBitree()
{
	puts("06：判别给定二叉树是否是完全二叉树。");
	BiTree T1 = createDefaultBiTree();
	printf("T1是否为完全二叉树？%d", isCompleteBitree(T1));

	/*
	  *				1
	  *          /		\
	  *        2		 3
	  *      /   \     /   \
	  *     4     5   6     7
	  *   /  \   /   
	  *	 8	  9 10
	  */
	BiElemType elems[] = { 1,2,4,8,'#','#',9,'#','#',5,10,'#','#','#',3,6,'#','#',7,'#','#' };
	BiTree T2 = NULL;
	InitBiTree(&T2, elems, sizeof(elems) / sizeof(elems[0]));
	printf("\nT2是否为完全二叉树？%d", isCompleteBitree(T2));
	DestroyBiTree(T1);
	DestroyBiTree(T2);
}

int doubleNodeCount(BiTree bitree)
{
	if (bitree == NULL) return 0;
	int leftCount = doubleNodeCount(bitree->left);
	int rightCount = doubleNodeCount(bitree->right);
	if (bitree->left && bitree->right)
		return leftCount + rightCount + 1;
	return leftCount + rightCount;
}

void testDoubleNodeCount()
{
	puts("07：假设二叉树采用二叉链表存储结构存储，试设计一个算法，计算一棵给定二叉树的所有双分支结点个数。");
	BiTree bitree = createDefaultBiTree();
	printf("二叉树双分支结点个数为：%d", doubleNodeCount(bitree));
	DestroyBiTree(bitree);
}

void swapLeftRight(BiTree bitree)
{
	if (bitree == NULL) return;
	BiNode* temp = bitree->left;
	bitree->left = bitree->right;
	bitree->right = temp;
	swapLeftRight(bitree->left);
	swapLeftRight(bitree->right);
	
}

void testSwapLeftRight()
{
	puts("08：设B是一棵采用链式结构存储的二叉树，编写一个把树B中所有结点的左、右子树进行交换的函数。");
	BiTree bitree = createDefaultBiTree();

	swapLeftRight(bitree);
	printf("交换左右子树后\n");
	 /*
	  *				34
	  *          /		\
	  *        39		24
	  *      /        /   \
	  *    64        28    18
	  *   /  \      /  \	 \
	  *	66	 42    32  27	  6
	  *		/	  			 /
	  *	   48			    14			  
	  */
	// 先序：34 39 64 66 42 48 24 28 32 27 18 6 14
	// 中序：66 64 48 42 39 34 32 28 27 24 18 14 6
	printf("先序：");
	PreOrder(bitree, printBiNode);
	printf("\n中序：");
	InOrder(bitree, printBiNode);
	DestroyBiTree(bitree);
}

BiElemType kValueOnPreOrderRecur(BiTree bitree)
{
	if (bitree == NULL) return 0;
	// 当前结点是第k个结点
	if (++k_count == pre_k) return bitree->elem;

	BiElemType leftRet = kValueOnPreOrderRecur(bitree->left);
	if (leftRet) // 在左子树找到了第k个结点，不再遍历右子树，返回结果
		return leftRet;
	return kValueOnPreOrderRecur(bitree->right);
}

bool kValueOnPreOrder(BiTree bitree, int k, BiElemType* kValue)
{
	Stack stack;
	InitStack(&stack);
	Stack* stack_ptr = &stack;
	BiNode* node = bitree;
	while (node || !IsEmpty(stack_ptr)) {
		if (node) {
			if (--k == 0) { // 当前结点是第k个结点
				*kValue = node->elem;
				return true;
			}
			Push(stack_ptr, node);
			node = node->left;
		}
		else {
			Pop(stack_ptr, &node);
			node = node->right;
		}
	}
	DestroyStack(stack_ptr);
	// 二叉树结点数少于k个
	return false;
}

void testKValueOnPreOrder()
{
	puts("09：假设二叉树采用二叉链表存储结构存储，设计一个算法，求先序遍历序列中第k(1≤k≤二叉树中结点个数)个结点的值。");
	BiTree bitree = createDefaultBiTree();

	BiElemType kValue = kValueOnPreOrderRecur(bitree);
	if (kValue)
		printf("递归遍历，先序第%d个结点值为：%d\n", pre_k, kValue);
	bool ret = kValueOnPreOrder(bitree, pre_k, &kValue);
	if (ret) 
		printf("非递归遍历，先序第%d个结点值为：%d\n", pre_k, kValue);

	DestroyBiTree(bitree);

}

void deleteSubTree(BiTree* bitree, BiElemType deletedX)
{
	if (*bitree == NULL) return;
	if ((*bitree)->elem == deletedX) {
		DestroyBiTree(*bitree);
		*bitree = NULL;
		return;
	}
	deleteSubTree(&(*bitree)->left, deletedX);
	deleteSubTree(&(*bitree)->right, deletedX);
}

void testDeleteSubTree()
{
	puts("10：已知二叉树以二叉链表存储，编写算法完成：对于树中每个元素值为x的结点，删除以它为根的子树，并释放相应的空间。");

	/*
	 * 用先序序列[34,24,18,6,#,14,#,#,#,18,27,#,#,32,#,#,39,#,64,18,#,48,#,#,18,#,#]初始化为一棵二叉树
	 *            34
	 *          /    \
	 *        24      39
	 *      /   \       \
	 *    18    18      64
	 *   /     /  \    /  \
	 *  6     27  32  18  18
	 *   \              \
	 *   14             48
	 */
	BiTree bitree = NULL;
	BiElemType elems[] = { 34,24,18,6,'#',14,'#','#','#',18,27,'#','#',32,'#','#',39,'#',64,18,'#',48,'#','#',18,'#','#' };
	InitBiTree(&bitree, elems, sizeof(elems) / sizeof(elems[0]));

	printf("删除前层序：");
	LevelOrder(bitree, printBiNode);

	deleteSubTree(&bitree, 18);
	/*
	 *            34
	 *          /    \
	 *        24      39
	 *			        \      
	 *					64
	 */
	printf("\n删除后层序：");
	LevelOrder(bitree, printBiNode);

	DestroyBiTree(bitree);
}

bool printAncestors(BiTree bitree, BiElemType x)
{
	if (bitree == NULL) return false;
	if (bitree->elem == x) return true;
	bool leftHasX = printAncestors(bitree->left, x);
	if (leftHasX) {
		printf("%d ", bitree->elem);
		return true;
	}
	bool rightHasX = printAncestors(bitree->right, x);
	if (rightHasX) {
		printf("%d ", bitree->elem);
		return true;
	}
	return false;
}

void testPrintAncestors()
{
	puts("11：在二叉树中查找值为x的结点，试编写算法（用C语言）打印值为x的结点的所有祖先，假设值为x的结点不多于一个。");
	BiTree bitree = createDefaultBiTree();
	printf("%d的祖先为：", 48);
	printAncestors(bitree, 48);
	DestroyBiTree(bitree);
}

bool ANCESTOR(BiTree ROOT, BiNode* p, BiNode* q, BiNode** r)
{
	return false;
}

void testANCESTOR()
{
}

int bitreeWidth(BiTree bitree)
{
	if (bitree == NULL) return 0;
	int height = bitreeHeight(bitree);
	int* count_arr = (int*)calloc(height + 1, sizeof(int));
	if (!count_arr) return 0;
	increaseWidth(bitree, 1, count_arr);
	// 找出最大宽度
	int width = 0;
	for (int i = 1; i < height + 1; ++i) {
		if (count_arr[i] > width)
			width = count_arr[i];
	}
	return width;
}

void increaseWidth(BiNode* node, int level, int count_arr[])
{
	if (node == NULL) return;
	++count_arr[level];
	increaseWidth(node->left, level + 1, count_arr);
	increaseWidth(node->right, level + 1, count_arr);
}

void testBitreeWidth()
{
	puts("13：假设二叉树采用二叉链表存储结构，设计一个算法，求非空二叉树b的宽度（即具有结点数最多的那一层的结点个数）。");
	BiTree bitree = createDefaultBiTree();
	printf("二叉树的宽度为：%d", bitreeWidth(bitree));
	DestroyBiTree(bitree);
}

void fullBiTreePreToPost(int pre[], int pre_begin, int pre_end, int post[], int post_end)
{
	// 先序序列已遍历完毕
	if (pre_begin > pre_end) return;

	post[post_end] = pre[pre_begin];
	// 左或者右子树结点数
	int subCount = (pre_end - pre_begin) / 2;
	fullBiTreePreToPost(pre, pre_begin + 1, pre_begin + subCount, post, post_end - subCount - 1);
	fullBiTreePreToPost(pre, pre_end - subCount + 1, pre_end, post, post_end - 1);
}

void testFullBiTreePreToPost()
{
	puts("14：设有一棵满二叉树（所有结点值均不同），已知其先序序列为pre，设计一个算法求其后序序列post。");
	/*
	 *            34
	 *          /    \
	 *        24      39
	 *      /   \    /  \
	 *     18   28  37  64
	 */
	int pre[] = { 34,24,18,28,39,37,64 };
	int post[7];
	fullBiTreePreToPost(pre, 0, 6, post, 6);
	// 后序序列：18 28 24 37 64 39 34
	printf("后序序列为：");
	for (int i = 0; i < 7; ++i)
		printf("%d ", post[i]);
}

void linkLeaf(BiTree bitree, BiNode** preLeaf)
{
	if (bitree == NULL) return;
	if (!bitree->left && !bitree->right) {
		(*preLeaf)->right = bitree;
		*preLeaf = bitree;
		return;
	}
	linkLeaf(bitree->left, preLeaf);
	linkLeaf(bitree->right, preLeaf);
}

void testLinkLeaf()
{
	puts("15：将二叉树的叶结点按从左到右的顺序链成一个单链表。");
	BiTree bitree = createDefaultBiTree();
	
	BiNode* head = newBiNode(0);
	BiNode* temp_head = head;
	linkLeaf(bitree, &temp_head);

	// 输出叶子结点
	printf("叶子结点为：");
	BiNode* p = head->right, *q;
	while (p) {
		printf("%d ", p->elem);
		q = p;
		p = p->right;
		// 恢复二叉树，方便回收内存空间
		q->right = NULL;
	}

	DestroyBiTree(bitree);
}

bool bitreeSimilarity(BiTree T1, BiTree T2)
{
	if (T1 ==NULL && T2 == NULL)
		return true;
	else if (T1 && !T2)
		return false;
	else if (!T1 && T2)
		return false;

	if (!bitreeSimilarity(T1->left, T2->left)) return false;
	return bitreeSimilarity(T1->right, T2->right);
}

void testBitreeSimilarity()
{
	puts("16：判断两棵二叉树是否相似。");
	BiTree T1 = createDefaultBiTree();
	//BiTree T2 = createDefaultBiTree();

	/*
	 *            34
	 *          /    \
	 *        24      39
	 *      /   \       \
	 *    18    18      64
	 *   /     /  \    /  
	 *  6     27  32  18  
	 *   \              \
	 *   14             48
	 */
	BiTree T2 = NULL;
	BiElemType elems[] = { 34,24,18,6,'#',14,'#','#','#',18,27,'#','#',32,'#','#',39,'#',64,18,'#',48,'#','#', '#'};
	InitBiTree(&T2, elems, sizeof(elems) / sizeof(elems[0]));

	printf("两棵树是否相似？%d", bitreeSimilarity(T1, T2));

	DestroyBiTree(T1);
	DestroyBiTree(T2);
}

int bitreeWPL(BiTree root, int level)
{
	if (root == NULL) return 0;
	if (!root->left && !root->right) {
		// 用elem表示权值weight
		return level * root->elem;
	}
	// 左子树的WPL
	int leftWPL = bitreeWPL(root->left, level + 1);
	int rightWPL = bitreeWPL(root->right, level + 1);
	return leftWPL + rightWPL;
}

void testBitreeWPL()
{
	puts("17：求二叉树T的带权路径长度WPL。");
	BiTree T = createDefaultBiTree();

	printf("T的WPL为：%d", bitreeWPL(T, 0));

	DestroyBiTree(T);
}

void printExpression(BiTree bitree)
{
	if (bitree == NULL) return;
	if (bitree->left || bitree->right) {// 不是叶子结点
		printf("(");
		// 打印左子树
		printExpression(bitree->left);
		printf("%c", bitree->elem);
		// 打印右子树
		printExpression(bitree->right);
		printf(")");
	} else // 叶子结点
		printf("%c", bitree->elem);
}

void testPrintExpression()
{
	puts("18：将给定的表达式树（二叉树）转换为等价的中缀表达式（通过括号反映操作符的计算次序）并输出。");
	/*
	 *			 *							+
	 *		/         \					/  		\
	 *	   +		   *			   *		 -
	 *	 /   \		 /   \			 /	 \		  \
	 *  a	  b	    c	  -		    a	  b		   -
	 *						\					 /	 \
	 *						 d					c	  d
	 */
	BiTree T1 = NULL;
	BiElemType elems1[] = { '*','+','a','#','#','b','#','#','*','c','#','#','-','#','d','#','#' };
	InitBiTree(&T1, elems1, sizeof(elems1) / sizeof(elems1[0]));

	BiTree T2 = NULL;
	BiElemType elems2[] = { '+','*','a','#','#','b','#','#','-','#','-','c','#','#','d','#','#' };
	InitBiTree(&T2, elems2, sizeof(elems2) / sizeof(elems2[0]));

	printf("表达式1：");
	printExpression(T1);
	printf("\n表达式2：");
	printExpression(T2);

	DestroyBiTree(T1);
	DestroyBiTree(T2);
}

bool SqBiTreeIsBST(SqBiTree *bitree)
{
	int *arr = bitree->SqBiTNode;
	// 分支结点个数
	int branchCount = bitree->ElemNum / 2;
	for (int i = 0; i < branchCount; ++i) {
		if (arr[i] == -1)
			continue;
		int left = arr[(i + 1) * 2 - 1];
		if (left != -1 && left > arr[i])
			return false;
		int right = arr[(i + 1) * 2];
		if (right != -1 && arr[i] > right)
			return false;
	}
	return true;
}

void InitSqBiTree(SqBiTree* bitree, int elems[], int len)
{
	for (int i = 0; i < len; ++i)
		bitree->SqBiTNode[i] = elems[i];
	bitree->ElemNum = len;
}

void testSqBiTreeIsBST()
{
	puts("王道19：判断采用顺序存储结构的二叉树是否是二叉排序树。");
	SqBiTree T1;
	int elems1[] = { 40 ,25 ,60 ,-1 ,30 ,-1 ,80 ,-1 ,-1 ,27 };
	InitSqBiTree(&T1, elems1, sizeof(elems1) / sizeof(int));
	SqBiTree T2;
	int elems2[] = { 40, 50, 60 ,-1 ,30 ,-1 ,-1 ,-1 ,-1 ,-1 ,35 };
	InitSqBiTree(&T2, elems2, sizeof(elems2) / sizeof(int));

	SqBiTree T3;
	/*
	 *            34
	 *          /    \
	 *        24      39
	 *      /   \       \
	 *    18    28      64
	 */
	int elems3[] = { 34,24,39,18,28,-1,64 };
	InitSqBiTree(&T3, elems3, sizeof(elems3) / sizeof(int));

	printf("T1是否是二叉排序树？%d", SqBiTreeIsBST(&T1));
	printf("\nT2是否是二叉排序树？%d", SqBiTreeIsBST(&T2));
	printf("\nT3是否是二叉排序树？%d", SqBiTreeIsBST(&T3));
}

int branchCount(BiTree bitree)
{
	if (bitree == NULL) return 0;
	int count = 0;
	ReusableLinkQueue queue;
	InitReusableQueue(&queue);
	BiNode* node = bitree;
	EnReusableQueue(&queue, node);
	while (!ReusableQueueEmpty(&queue)) {
		DeReusableQueue(&queue, &node);
		if (node->left || node->right)
			++count;
		if (node->left)
			EnReusableQueue(&queue, node->left);
		if (node->right)
			EnReusableQueue(&queue, node->right);
	}

	DestroyReusableQueue(&queue);
	return count;
}

void testBranchCount()
{
	puts("如果以二叉链表作为存储结构，试用类C语言编写统计二叉树非叶子结点个数的层次遍历算法。");
	BiTree bitree = createDefaultBiTree();

	printf("非叶子结点个数为：%d", branchCount(bitree));

	DestroyBiTree(bitree);
}

void exchangeLeftRight(BiNode *node)
{
	BiNode* temp = node->left;
	node->left = node->right;
	node->right = temp;
}
void testExchangeLeftRight()
{
	puts("用非递归算法交换二叉树的左右子树");
	BiTree bitree = createDefaultBiTree();

	PostOrder(bitree, exchangeLeftRight);

	// 先序：34 39 64 66 42 48 24 28 32 27 18 6 14
	// 中序：66 64 48 42 39 34 32 28 27 24 18 14 6
	printf("先序：");
	PreOrder(bitree, printBiNode);
	printf("\n中序：");
	InOrder(bitree, printBiNode);

	DestroyBiTree(bitree);
}

int leafLongestDistance(BiTree bitree)
{
	return bitreeHeight(bitree->left) + bitreeHeight(bitree->right);
}

void testLeafLongestDistance()
{
	puts("二叉树用二叉链表结构进行存储。请编写算法求二叉树根结点左右子树相隔最远的叶子结点之间距离。");
	BiTree bitree = createDefaultBiTree();

	printf("叶子结点之间最远距离为：%d", leafLongestDistance(bitree));

	DestroyBiTree(bitree);
}

bool bitreeIsEqual(BiTree T1, BiTree T2)
{
	if (T1 == T2) // 同一棵二叉树，或都是空树，则返回true
		return true;
	else if (T1 == NULL || T2 == NULL) // 有一棵为空树，另一棵不是空树，返回false
		return false;
	
	if (T1->elem != T2->elem)
		return false;
	if (!bitreeIsEqual(T1->left, T2->left))
		return false;
	if (!bitreeIsEqual(T1->right, T2->right))
		return false;
	return true;
}

bool isSubTree(BiTree A, BiTree B)
{
	if (A == NULL || B == NULL) return false;
	if (A->elem == B->elem && bitreeIsEqual(A, B))
		return true;
	if (isSubTree(A->left, B))
		return true;
	return isSubTree(A->right, B);
}

void testIsSubTree()
{
	puts("对于两棵给定的二叉树A和B，判断B是不是A的子结构");
	BiTree A = createDefaultBiTree();

	/*
	 *		28
	 *	  /	   \
	 *   27	   32
	 */
	BiTree B = NULL;
	BiElemType elems[] = { 28,27,'#','#',32,'#','#' };
	InitBiTree(&B, elems, sizeof(elems) / sizeof(elems[0]));
	printf("B是否是A的子结构？%d\n", isSubTree(A, B));


	BiTree C = newBiNode(48);
	printf("C是否是A的子结构？%d\n", isSubTree(A, C));

	/*
	 *		42
	 *	   /
	 *	 48
	 */
	BiTree D = newBiNode(42);
	D->left = C;
	printf("D是否是A的子结构？%d\n", isSubTree(A, D));

	DestroyBiTree(A);
	DestroyBiTree(B);
	DestroyBiTree(D);
}

BiNode* bitreeExpandToList(BiNode* root)
{
	if (root == NULL || root->left == NULL && root->right == NULL) // 空结点或叶子结点，直接返回
		return root;
	BiNode *left_last = bitreeExpandToList(root->left);
	BiNode *right_last = bitreeExpandToList(root->right);

	if (left_last) {
		left_last->right = root->right;
		root->right = root->left;
		root->left = NULL;
	}
	return right_last ? right_last : left_last;
}

void testBitreeExpandToList()
{
	puts("leetcode:114. 二叉树展开为链表");
	BiTree bitree = createDefaultBiTree();

	bitreeExpandToList(bitree);
	printf("展开后：");
	BiNode* p = bitree;
	while (p) {
		printBiNode(p);
		p = p->right;
	}
	DestroyBiTree(bitree);
}
