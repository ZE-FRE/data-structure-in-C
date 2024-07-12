#ifndef SQLIST_H_
#define SQLIST_H_

#include <stdbool.h>

/*
 * 顺序表，用动态数组实现
 */

#define SQ_INIT_CAPACITY 5
#define SQ_INCREMENT 5

typedef int SqElemType;

/*
 * 类型定义：将一个“比较函数指针”定义为一个类型
 */
typedef bool (*Compare)(const SqElemType e1, const SqElemType e2);
/* 
 * 类型定义：将一个“访问函数指针”定义为一个类型
 */
typedef void (*VisitSqElem)(SqElemType elem);

typedef struct {
	// 动态数组基址
	SqElemType* base;
	// 线性表当前长度
	int length;
	// 线性表容量
	int capacity;
} SqList;

// 重要
bool InitSqList(SqList* list);

void DestroySqList(SqList* list);

void ClearSqList(SqList* list);

bool SqListEmpty(const SqList* list);

int SqListLength(const SqList* list);

bool GetSqElem(const SqList* list, int i, SqElemType* elem);

/*
 * 返回顺序表中第一个元素与elem满足compare关系的位序
 * 若没有这样的元素，返回0
 */
int LocateSqElem(const SqList* list, const SqElemType elem, Compare compare);

bool PriorSqElem(const SqList* list, const SqElemType cur, SqElemType* pre);

bool NextSqElem(const SqList* list, const SqElemType cur, SqElemType* next);

/*
 * 超级重要
 * 在第i个结点插入，1 <= i <= SqListLength()+1
 * 将第i个到第n个结点向后移动，在第i个位置插入新结点。
 * 实际效果为：在原来的第i个结点前插入一个新结点
 * 
 * 平均移动次数为：n/2
 */
bool SqListInsert(SqList* list, int i, const SqElemType elem);

/*
 * 超级重要
 * 将第i个结点删除，1 <= i <= SqListLength()
 * 
 * 平均移动次数为：(n-1)/2
 */
bool SqListDelete(SqList* list, int i, SqElemType* elem);

// 重要
void SqListTraverse(const SqList* list, VisitSqElem visit);

/*
 * 顺序表取并集，La∪Lb，将在Lb中而不在La中的数据元素插入到La中
 */
void UnionSqList(SqList* La, const SqList *Lb);


bool sqElemEqauls(const SqElemType elem1, const SqElemType elem2);

void printSqElem(const SqElemType elem);
void testSqList();

#endif
