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
	SqList list;
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
	DestroySqList(&list2);
}
