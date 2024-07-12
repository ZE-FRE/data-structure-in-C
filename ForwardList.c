#include "ForwardList.h"
#include <stdlib.h>
#include <stdio.h>

bool InitList(ForwardList* list)
{
    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    if (!head) return false;
    head->next = NULL;
    *list = head;
    return true;
}

void DestroyList(ForwardList* list)
{
    ListNode* head = *list;
    ListNode* p = head->next;
    ListNode* q;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    free(head);
    *list = NULL;
}

void ClearList(ForwardList list)
{
    ListNode* p = list->next;
    ListNode* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    list->next = NULL;
}

bool ListEmpty(const ForwardList list)
{
    return list->next == NULL;
}

int ListLength(const ForwardList list)
{
    ListNode* p = list->next;
    int length = 0;
    while (p) {
        ++length;
        p = p->next;
    }
    return length;
}

bool GetListElem(const ForwardList list, int i, ListElemType* elem)
{
    ListNode* p = list;
    while (p && i > 0) {
        p = p->next;
        --i;
    }
    if (p) {
        *elem = p->elem;
        return true;
    }
    return false;
}

int LocateListElem(const ForwardList list, const ListElemType elem)
{
    ListNode* p = list->next;
    int i = 1;
    while (p) {
        if (p->elem == elem) return i;
        p = p->next;
        ++i;
    }
    return -1;
}

bool PriorListElem(const ForwardList list, const ListElemType cur, ListElemType* pre)
{
    // 空链表或链表只有一个结点
    if (!list->next || !list->next->next) return false;
    ListNode* prior = list;
    ListNode* p = list->next;
    while (p) {
        if (p->elem == cur) {
            *pre = prior->elem;
            return true;
        }
        prior = p;
        p = p->next;
    }
    return false;
}

bool NextListElem(const ForwardList list, const ListElemType cur, ListElemType* next)
{
    ListNode* p = list->next;
    while (p) {
        if (p->elem == cur && p->next) {
            *next = p->next->elem;
            return true;
        }
        p = p->next;
    }
    return false;
}

bool ListInsert(ForwardList list, int i, const ListElemType elem)
{
    if (i < 1) return false;
    // p指向插入结点的前一个结点
    ListNode* p = list;
    int j = 1;
    while (p && j < i) {
        p = p->next;
        ++j;
    }
    if (!p) return false;
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (!newNode) return false;
    newNode->elem = elem;
    newNode->next = p->next;
    p->next = newNode;
    return true;
}

bool ListDelete(ForwardList list, int i, ListElemType* elem)
{
    if (i < 1) return false;
    // 寻找第i个结点，p指向其前驱
    ListNode* p = list;
    int j = 1;
    while (p->next && j < i) {
        p = p->next;
        ++j;
    }
    if (!p->next) return false;
    ListNode* deletedNode = p->next;
    p->next = deletedNode->next;
    *elem = deletedNode->elem;
    free(deletedNode);
    return true;
}

void printListElem(const ListElemType elem)
{
    printf("%d ", elem);
}

void ListTraverse(const ForwardList list, VisitListElem visit)
{
    ListNode* p = list->next;
    while (p) {
        visit(p->elem);
        p = p->next;
    }
}

void MergeList(ForwardList* La, ForwardList* Lb)
{
    // 遍历La的指针
    ListNode* pa = (*La)->next;
    // 遍历Lb的指针
    ListNode* pb = (*Lb)->next;
    // 合并后的链表
    ForwardList Lc;
    // 指向Lc表尾
    ListNode* pc = *La;
    while (pa && pb) {
        if (pa->elem < pb->elem) {
            pc->next = pa;
            pa = pa->next;
            pc = pc->next;
        }
        else {
            pc->next = pb;
            pb = pb->next;
            pc = pc->next;
        }
    }
    // 插入剩余段
    pc->next = pa ? pa : pb;
    // 释放链表Lb头结点
    free(*Lb);
}


void testForwardList()
{
    ForwardList list;
    InitList(&list);
    for (int i = 1; i <= 6; ++i) 
        ListInsert(list, 1, i);
    printf("list length: %d\n", ListLength(list));
    printf("print list：");
    ListTraverse(list, printListElem);

    
    ListElemType elem;
    if (GetListElem(list, 4, &elem)) {
        printf("\n===============\n");
        printf("第4个元素是：%d", elem);
    }

    int i = LocateListElem(list, 3);
    if (i) {
        printf("\n===============\n");
        printf("3是第%d个元素", i);
    }
    
    ListElemType pre;
    if (PriorListElem(list, 4, &pre)) {
        printf("\n===============\n");
        printf("4前面是：%d", pre);
    }
    ListElemType next;
    if (NextListElem(list, 4, &next)) {
        printf("\n===============\n");
        printf("4后面是：%d", next);
    }

    ListDelete(list, 3, &elem);
    ListDelete(list, 3, &elem);
    printf("\n===============\n");
    printf("删除两个元素后，print list：");
    ListTraverse(list, printListElem);

    ClearList(list);
    printf("\n===============\n");
    printf("清空单链表后：");
    printf("list length = %d,", ListLength(list));
    printf("\tprint list：");
    ListTraverse(list, printListElem);

    DestroyList(&list);


    printf("\n\n===============\n");
    printf("合并两个有序的链表");
    ForwardList La, Lb;
    InitList(&La);
    InitList(&Lb);

    for (int i = 10; i >= 1; i -= 2)
        ListInsert(La, 1, i);
    for (int i = 9; i >= 1; i -= 2)
        ListInsert(Lb, 1, i);
    printf("\n===============\n");
    printf("La：");
    ListTraverse(La, printListElem);
    printf("\n===============\n");
    printf("Lb：");
    ListTraverse(Lb, printListElem);

    printf("\n合并La和Lb");
    MergeList(&La, &Lb);
    printf("\n===============\n");
    printf("合并后的链表：");
    ListTraverse(La, printListElem);
    DestroyList(&La);
}
