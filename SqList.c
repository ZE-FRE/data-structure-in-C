#include "SqList.h"
#include <stdlib.h>
#include <stdio.h>

bool InitSqList(SqList* list)
{
	SqElemType* p = (SqElemType*)malloc(sizeof(SqElemType) * SQ_INIT_CAPACITY);
	if (!p) return false;
	list->base = p;
	list->length = 0;
	list->capacity = SQ_INIT_CAPACITY;
	return true;
}

void DestroySqList(SqList* list)
{
	free(list->base);
}

void ClearSqList(SqList* list)
{
	list->length = 0;
}

bool SqListEmpty(const SqList* list)
{
	return list->length == 0;
}

int SqListLength(const SqList* list)
{
	return list->length;
}

bool GetSqElem(const SqList* list, int i, SqElemType* elem)
{
	SqElemType* p = list->base;
	if (i < 0 || i > SqListLength(list))
		return false;
	*elem = list->base[i - 1];
	return true;
}

int LocateSqElem(const SqList* list, const SqElemType elem, Compare compare)
{
	int length = SqListLength(list);
	int i = 0;
	while (i < length) {
		if (compare(elem, list->base[i++]))
			return i;
	}
	return 0;
}

bool PriorSqElem(const SqList* list, const SqElemType cur, SqElemType* pre)
{
	int curPos = LocateSqElem(list, cur, sqElemEqauls);
	// 未找到或是第一个元素
	if (curPos <= 1) return false;
	*pre = list->base[curPos - 2];
	return true;
}

bool NextSqElem(const SqList* list, const SqElemType cur, SqElemType* next)
{
	int curPos = LocateSqElem(list, cur, sqElemEqauls);
	// 未找到或是最后一个元素
	if (curPos == -1 || curPos == SqListLength(list)) return false;
	*next = list->base[curPos];
	return true;
}

bool SqListInsert(SqList* list, int i, const SqElemType elem)
{
	int length = SqListLength(list);
	if (i < 1 || i > length + 1) return false;
	if (length == list->capacity) { // 满了
		int newCapacity = list->capacity + SQ_INCREMENT;
		SqElemType* newBase = (SqElemType*)realloc(list->base, newCapacity * sizeof(SqElemType));
		if (!newBase) return false;
		list->base = newBase;
		list->capacity = newCapacity;
	}
	// 插入位置
	SqElemType* p = &(list->base[i-1]);
	// 用于移动元素的指针
	SqElemType* q = &(list->base[length]);
	// 移动元素
	while (p != q) {
		*q = *(q - 1);
		--q;
	}
	*p = elem;
	// 表长+1
	++list->length;
	return true;
}

bool SqListDelete(SqList* list, int i, SqElemType* elem)
{
	if (i < 1 || i > list->length) return false;
	// 删除位置
	SqElemType* p = list->base + i - 1;
	// 尾后指针
	SqElemType* end = list->base + list->length;
	while (p != end) {
		*p = *(p + 1);
		++p;
	}
	// 表长-1
	--list->length;
	return true;
}

void SqListTraverse(const SqList* list, VisitSqElem visit)
{
	int length = SqListLength(list);
	for (int i = 0; i < length; ++i)
		visit(list->base[i]);
}

void UnionSqList(SqList* La, const SqList *Lb)
{
	int La_length = SqListLength(La);
	int Lb_length = SqListLength(Lb);
	SqElemType elem;
	for (int i = 1; i <= Lb_length; ++i) {
		GetSqElem(Lb, i, &elem);
		if (!LocateSqElem(La, elem, sqElemEqauls))
			SqListInsert(La, ++La_length, elem);
	}
}

bool sqElemEqauls(const SqElemType elem1, const SqElemType elem2)
{
	return elem1 == elem2;
}

void printSqElem(const SqElemType elem)
{
	printf("%d ", elem);
}

void testSqList()
{
	/*SqList list;
	InitSqList(&list);
	for (int i = 1; i <= 6; ++i)
		SqListInsert(&list, 1, i);
	SqListTraverse(&list, printSqElem);
	printf("\n===============\n");

	SqElemType elem;
	SqListDelete(&list, 3, &elem);
	SqListDelete(&list, 3, &elem);
	SqListTraverse(&list, printSqElem);

	SqList list2;
	InitSqList(&list2);
	SqListInsert(&list2, 1, 3);
	SqListInsert(&list2, 2, 4);
	UnionSqList(&list, &list2);

	printf("\n===============\n");
	SqListTraverse(&list, printSqElem);

	DestroySqList(&list);
	DestroySqList(&list2);*/

	

	/*==========王道书第2章顺序表算法题测试=========*/
	//testReverseSqList();

	//testRemoveDuplicates();

	//testMergeSqList();

	testExchangeTwoSqList();

	//testFindMedian();
}



/*==========王道书第2章顺序表算法题=========*/

void reverseSqList(SqList* list)
{
	SqElemType* p1 = list->base;
	SqElemType* p2 = list->base + list->length - 1;
	SqElemType temp;
	while (p1 < p2) {
		// swap
		temp = *p1;
		*p1 = *p2;
		*p2 = temp;
		++p1;
		--p2;
	}
}

void testReverseSqList()
{
	SqList list;
	InitSqList(&list);
	int elems[] = { 1,2,3,4,5,6,7,8,9 };
	int len = sizeof(elems) / sizeof(elems[0]);
	for (int i = 1; i <= len; ++i)
		SqListInsert(&list, i, elems[i - 1]);

	printf("王道02：设计一个高效算法，将顺序表L的所有元素逆置，要求算法的空间复杂度为O(1)\n");
	printf("初始线性表：");
	SqListTraverse(&list, printSqElem);
	reverseSqList(&list);
	printf("\n逆置后：");
	SqListTraverse(&list, printSqElem);
	DestroySqList(&list);
}

void removeDuplicates(SqList* list)
{
	if (SqListEmpty(list)) return;
	// 插入指针
	SqElemType* insert = list->base;
	// 遍历指针
	SqElemType *p = list->base;
	// 指向最后一个元素的指针
	SqElemType* end = list->base + list->length - 1;
	while (p != end) {
		if (*p == *(p + 1)) {
			++p;
			continue;
		}
		*insert = *p;
		++insert;
		++p;
	}
	// 处理最后一个元素
	*insert = *p;
	++insert;
	list->length = insert - list->base;
}

void testRemoveDuplicates()
{
	SqList list;
	InitSqList(&list);
	int elems[] = { 1,1,1,1,2,2,3,3,3,4,5,6,6,7,7,8,8,9,9 };
	int len = sizeof(elems) / sizeof(elems[0]);
	for (int i = 1; i <= len; ++i)
		SqListInsert(&list, i, elems[i - 1]);

	printf("王道05：从有序顺序表中删除所有其值重复的元素，使表中的元素均不同\n");
	printf("初始线性表：");
	SqListTraverse(&list, printSqElem);
	removeDuplicates(&list);
	printf("\n删除重复元素后：");
	removeDuplicates(&list);
	SqListTraverse(&list, printSqElem);
	DestroySqList(&list);
}

SqList mergeSqList(const SqList* list1, const SqList* list2)
{
	SqList list3;
	InitSqList(&list3);
	int p1 = 0, len1 = SqListLength(list1);
	int p2 = 0, len2 = SqListLength(list2);
	int p3 = 0;

	while (p1 < len1 && p2 < len2) {
		if (list1->base[p1] <= list2->base[p2])
			SqListInsert(&list3, p3++, list1->base[p1++]);
		else 
			SqListInsert(&list3, p3++, list2->base[p2++]);
	}
	while (p1 < len1)
		SqListInsert(&list3, p3++, list1->base[p1++]);
	while (p2 < len2)
		SqListInsert(&list3, p3++, list2->base[p2++]);
	return list3;
}

void testMergeSqList()
{
	SqList list1;
	InitSqList(&list1);
	int elems1[] = { 1,1,3,5,7,9 };
	int len1 = sizeof(elems1) / sizeof(elems1[0]);
	for (int i = 1; i <= len1; ++i)
		SqListInsert(&list1, i, elems1[i - 1]);

	SqList list2;
	InitSqList(&list2);
	int elems2[] = { 2,4,4,6,8,9,10 };
	int len2 = sizeof(elems2) / sizeof(elems2[0]);
	for (int i = 1; i <= len2; ++i)
		SqListInsert(&list2, i, elems2[i - 1]);

	printf("王道06：将两个有序顺序表合并为一个新的有序顺序表，并由函数返回结果顺序表\n");
	printf("线性表1：");
	SqListTraverse(&list1, printSqElem);
	printf("\n线性表2：");
	SqListTraverse(&list2, printSqElem);

	SqList list3 = mergeSqList(&list1, &list2);
	printf("\n合并后的线性表3：");
	SqListTraverse(&list3, printSqElem);

	DestroySqList(&list1);
	DestroySqList(&list2);
	DestroySqList(&list3);

}


void exchangeTwoSqList(SqList* list, int m, int n)
{
	int* A = list->base;
	int* Temp = (int*)malloc(sizeof(int) * m);
	if (!Temp) return;
	// 保存A[0,...,m-1]
	for (int i = 0; i < m; ++i)
		Temp[i] = A[i];
	// 将A[m,...,n+m-1]左移m个位置
	for (int i = 0; i < n; ++i)
		A[i] = A[i + m];
	// 把Temp中的a1~am拷贝到A[n,...,m+n-1]
	for (int i = 0, j = n; i < m; ++i, ++j)
		A[j] = Temp[i];
	free(Temp);
}

void testExchangeTwoSqList()
{
	SqList list;
	InitSqList(&list);
	int elems[] = { 1,2,3,4,5,6,7,8,9,10 };
	int len = sizeof(elems) / sizeof(elems[0]);
	for (int i = 1; i <= len; ++i)
		SqListInsert(&list, i, elems[i - 1]);

	printf("王道07：将数组中两个顺序表的位置互换\n");
	printf("初始线性表：");
	SqListTraverse(&list, printSqElem);
	exchangeTwoSqList(&list, 6, 4);
	printf("\n交换后：");
	SqListTraverse(&list, printSqElem);
	DestroySqList(&list);
}

int findMedian(const int S1[], const int S2[], int len)
{
	if (len < 1) return -1;
	int *p1 = S1, *p2 = S2, *median_ptr = NULL;
	while (len > 0) {
		if (*p1 < *p2)
			median_ptr = p1++;
		else
			median_ptr = p2++;
		--len;
	}
	return *median_ptr;
}

void testFindMedian()
{
	int S1[] = { 11,13,15,17,19 };
	int S2[] = { 2,4,6,8,20 };
	printf("王道11：找两个等长升序序列的中位数\n");
	int median = findMedian(S1, S2, 5);
	printf("中位数为：%d", median);

	int S3[] = { 1,2,5,9 };
	int S4[] = { 2,4,6,8 };
	median = findMedian(S3, S4, 4);
	printf("\n中位数为：%d", median);
}



/*==========王道书第2章顺序表算法题=========*/
