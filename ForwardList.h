#ifndef FORWARD_LIST_H_
#define FORWARD_LIST_H_

#include <stdbool.h>

/*
 * 带头结点的单链表
 */

typedef int ListElemType;

typedef struct ListNode {
	ListElemType elem;
	struct ListNode* next;
} ListNode, *ForwardList;

bool InitList(ForwardList* list);

void DestroyList(ForwardList* list);

void ClearList(ForwardList list);

bool ListEmpty(const ForwardList list);

int ListLength(const ForwardList list);

bool GetListElem(const ForwardList list, int i, ListElemType* elem);

int LocateListElem(const ForwardList list, const ListElemType elem);

bool PriorListElem(const ForwardList list, const ListElemType cur, ListElemType* pre);

bool NextListElem(const ForwardList list, const ListElemType cur, ListElemType* next);

bool ListInsert(ForwardList list, int i, const ListElemType elem);

bool ListDelete(ForwardList list, int i, ListElemType* elem);

typedef void (*VisitListElem)(ListElemType elem);
void printListElem(const ListElemType elem);
void ListTraverse(const ForwardList list, VisitListElem visit);

/*
 * 合并两个有序的链表，合并后Lb被释放，La为合并后的链表
 */
void MergeList(ForwardList* La, ForwardList* Lb);

void SortList(ForwardList list);

void testForwardList();

#endif

