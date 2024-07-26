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



/*==========王道书第2章顺序表算法题=========*/

/*
 * 02：设计一个高效算法，将顺序表L的所有元素逆置，要求算法的空间复杂度为O(1)
 * date:2024/7/26
 * 思路：双指针，一个指向头，一个指向尾，向中间靠近，p1 >= p2时退出循环
 */
void reverseSqList(SqList *list);
void testReverseSqList();

/* 
 * 05：从有序顺序表中删除所有其值重复的元素，使表中的元素均不同
 * date:2024/7/25
 */
void removeDuplicates(SqList* list);
void testRemoveDuplicates();

/*
 * 06：将两个有序顺序表合并为一个新的有序顺序表，并由函数返回结果顺序表
 * date:2024/7/25
 */
SqList mergeSqList(const SqList* list1, const SqList* list2);
void testMergeSqList();

/*
 * 07：已知在一维数组A[m+n]中依次存放两个线性表(a1,a2,a3,...,am)和(b1,b2,b3,...,bn)。
 * 编写一个函数，将数组中两个顺序表的位置互换，即将(b1,b2,b3,...,bn)放在(a1,a2,a3,...,am)的前面。
 * date:2024/7/26
 * 思路：用一个数组Temp[0,...,m-1]存放a1~am，然后把b1~bn拷贝到A[0,...,n-1]，接着把Temp中的a1~am拷贝到A[n,...,m+n-1]
 * 时间复杂度：O(m+n+m)
 * 空间复杂度：O(m)
 */
// assert list->length == m + n;
void exchangeTwoSqList(SqList* list, int m, int n);
void testExchangeTwoSqList();

/*
 * 11(2011统考真题)：一个长度为L（L≥1）的升序序列S，处在 第L/2向上取整 个位置的数称为S的中位数。
 * 例如，若序列S1=(11,13,15,17,19)，则S1的中位数为15，两个序列的中位数是含它们所有元素的升序序列的中位数。
 * 例如，若S2=(2,4,6,8,20)，则S1和S2的中位数是11。现有两个等长序列A和B，
 * 试设计一个在时间和空间两方面都尽可能高效的算法，找出两个序列A和B的中位数。
 * date:2024/7/26
 * 思路：归并的思路，中位数刚好是归并后第len个元素，由于两序列等长，所以一个循环就够了
 */
int findMedian(const int S1[], const int S2[], int len);
void testFindMedian();


/*==========王道书第2章顺序表算法题=========*/


#endif
