#include <stdlib.h>
#include <stdio.h>
#include "../include/ForwardList.h"

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
    // 指向合并后链表的表尾
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

void SortList(ForwardList list)
{
    ListNode* minNode = NULL;
    for (ListNode* p = list->next; p; p = p->next) {
        minNode = p;
        for (ListNode* q = p->next; q; q = q->next) 
            if (q->elem < minNode->elem)
                minNode = q;
        if (minNode != p) {
            ListElemType temp = p->elem;
            p->elem = minNode->elem;
            minNode->elem = temp;
        }
    }
}

void printList(const ForwardList list)
{
    if (!ListEmpty(list))
        ListTraverse(list, printListElem);
}

ListNode* newListNode(ListElemType elem)
{
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (!newNode) return NULL;
    newNode->elem = elem;
    newNode->next = NULL;
    return newNode;
}

ForwardList createListFromArray(const int arr[], int len)
{
    ForwardList list = NULL;
    InitList(&list);
    for (int i = 0; i < len; ++i) 
        ListInsert(list, i + 1, arr[i]);
    return list;
}


void testForwardList()
{
    /*
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

    printf("\n===============\n");
    printf("SortList：\n");
    ForwardList L;
    InitList(&L);
    ListInsert(L, 1, 4);
    ListInsert(L, 2, 8);
    ListInsert(L, 3, 1);
    ListInsert(L, 4, 28);
    ListInsert(L, 5, 16);
    ListInsert(L, 3, 10);
    ListInsert(L, 2, 8);
    ListInsert(L, 1, 48);
    ListInsert(L, 4, 30);
    printf("链表数据为：");
    ListTraverse(L, printListElem);

    SortList(L);
    printf("\n===============\n");
    printf("选择排序后链表数据为：");
    ListTraverse(L, printListElem);
    DestroyList(&L);
    */

    //testListDeleteElem();

    //testListDeleteMin();

    //testReverseList();
    
    //testListDeleteRange();
    
    //testSeparateList();

    //testListDeleteDuplicates();

    //testFindListShared();
    
    //testFindSharedStoreInA();

    //testListIsSub();

    //testListRightShift();

    //testRingForCyclicList();
    //testListRingExists();

    //testFindListLastK();

    //testTwinSum();

    //testFindSharedSuffix();

    //testListDeleteAbsDuplicates();

    //testRearrangeList();

    //testSiftRepetition();

    //testIsSymmetricList();

    //testListMid();

    //testListSum();

    testDeleteListDuplicates();

}

void listDeleteElem(ForwardList list, ListElemType elem)
{
    ListNode* p = list, *q;
    while (p->next) {
        q = p->next;
        if (q->elem == elem) {
            p->next = q->next;
            free(q);
        } else
            p = q;
    }
}
void testListDeleteElem()
{
    
    int elems[] = { 1,2,3,4,4,4,4,5,6 };
    ForwardList list = createListFromArray(elems, sizeof(elems) / sizeof(elems[0]));

    printf("王道01：在带头结点的单链表L中，删除所有值为x的结点，并释放其空间。\n");
    printf("初始链表：");
    printList(list);

    listDeleteElem(list, 4);
    printf("\n删除4后：");
    printList(list);
    DestroyList(&list);
}

void listDeleteMin(ForwardList list)
{
    if (ListEmpty(list)) return;
    ListNode* pre = list, *p = list->next;
    // 指向最小值结点的前驱
    ListNode* min_pre_ptr = list;
    while (p) {
        if (p->elem < min_pre_ptr->next->elem) {
            min_pre_ptr = pre;
        }
        pre = p;
        p = p->next;
    }

    ListNode* q = min_pre_ptr->next;
    min_pre_ptr->next = q->next;
    free(q);
}
void testListDeleteMin()
{
    int elems[] = { 8,18,7,12,6,9,21,11,2,4,1 };
    ForwardList list = createListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
    printf("王道02：试编写在带头结点的单链表L中删除一个最小值结点的高效算法（假设该结点唯一）。\n");
    printf("初始链表：");
    printList(list);

    listDeleteMin(list);
    printf("\n删除最小值后：");
    printList(list);
    DestroyList(&list);
}

void reverseList(ForwardList list)
{
    // 以原链表的头结点作为新链表的头结点，p作为遍历结点
    ListNode* head = list, *p = list->next;
    // 新链表长度为0
    head->next = NULL;
    ListNode* q;
    while (p) {
        q = p->next;
        p->next = head->next;
        head->next = p;
        p = q;
    }
}
void testReverseList()
{
    int elems[] = { 1,2,3,4,4,4,4,5,6 };
    ForwardList list = createListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
    puts("王道03：试编写算法将带头结点的单链表就地逆置，所谓“就地”是指辅助空间复杂度为O(1)。");
    printf("初始链表：");
    printList(list);

    reverseList(list);
    printf("\n逆置后：");
    printList(list);
    DestroyList(&list);
}

void listDeleteRange(ForwardList list, int s, int t)
{
    ListNode* pre = list, *p = list->next;
    // 用于释放指针
    ListNode *q;
    while (p) {
        if (s <= p->elem && p->elem <= t) {
            q = p;
            p = p->next;
            pre->next = p;
            free(q);
        }
        else {
            pre = p;
            p = p->next;
        }
    }
}
void testListDeleteRange()
{
    int elems[] = { 1,2,3,4,4,4,4,5,6 };
    ForwardList list = createListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
    puts("王道04：删除链表中所有介于给定的两个值（作为函数参数给出）之间的元素（若存在）。");
    printf("初始链表：");
    printList(list);

    listDeleteRange(list, 3, 5);
    printf("\n删除后：");
    printList(list);
    DestroyList(&list);
}

void separateList(ForwardList Lc, ForwardList* La, ForwardList* Lb)
{
    *La = Lc;
    InitList(Lb);

    ListNode *pca = Lc->next, *pcb, *pa = *La, *head_b = *Lb;
    while (pca) {
        pcb = pca->next;
        // 插入La
        pa->next = pca;
        pa = pa->next;

        // 移动遍历Lc的指针
        pca = pca->next->next;
        
        pa->next = NULL;

        // 头插法插入Lb
        pcb->next = head_b->next;
        head_b->next = pcb;
    }
}
void testSeparateList()
{
    int elems[] = { 1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9 };
    ForwardList list = createListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
    puts("王道06：将C={a1,b1,a2,b2,...,an,bn}拆分为A={a1,a2,...,an}，B={bn,...,b2,b1}。");
    printf("初始链表：");
    printList(list);

    ForwardList La, Lb;
    separateList(list, &La, &Lb);
    printf("\n拆分后\n");
    printf("La=");
    printList(La);
    printf("\nLb=");
    printList(Lb);
    DestroyList(&La);
    DestroyList(&Lb);
}

void listDeleteDuplicates(ForwardList list)
{
    if (ListEmpty(list)) return;
    ListNode *pre = list->next, *p = pre->next;
    // 用于删除
    ListNode *q;
    while (p) {
        if (p->elem == pre->elem) {
            q = p;
            p = p->next;
            pre->next = p;
            free(q);
        }
        else {
            pre = p;
            p = p->next;
        }
    }
}
void testListDeleteDuplicates()
{
    int elems[] = { 1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9 };
    ForwardList list = createListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
    puts("王道07：在一个递增有序的单链表中，存在重复的元素。设计算法删除重复的元素。");
    printf("初始链表：");
    printList(list);

    listDeleteDuplicates(list);
    printf("\n删除重复元素后：");
    printList(list);
    DestroyList(&list);
}

ForwardList findListShared(ForwardList La, ForwardList Lb)
{
    ForwardList Lc;
    InitList(&Lc);

    ListNode *pa = La->next, *pb = Lb->next, *pc = Lc;
    while (pa && pb) {
        if (pa->elem < pb->elem)
            pa = pa->next;
        else if (pa->elem > pb->elem)
            pb = pb->next;
        else {
            ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
            if (!newNode) return Lc;
            newNode->elem = pa->elem;
            newNode->next = NULL;
            pc->next = newNode;
            pc = pc->next;
            pa = pa->next;
            pb = pb->next;
        }
    }
    return Lc;
}

void testFindListShared()
{
    int elems1[] = { 1,2,3,5,8,10,11 };
    ForwardList La = createListFromArray(elems1, sizeof(elems1) / sizeof(elems1[0]));
    int elems2[] = { 2,3,4,5,7,10,12 };
    ForwardList Lb = createListFromArray(elems2, sizeof(elems2) / sizeof(elems2[0]));

    puts("王道08：设A和B是两个单链表，元素递增有序。设计一个算法从A和B中的公共元素产生链表C，要求不破坏A、B的结点。");
    printf("La=");
    printList(La);
    printf("\nLb=");
    printList(Lb);

    ForwardList Lc = findListShared(La, Lb);
    printf("\n公共元素为：\n");
    printf("Lc=");
    printList(Lc);
    DestroyList(&La);
    DestroyList(&Lb);
    DestroyList(&Lc);
}

void findSharedStoreInA(ForwardList La, ForwardList Lb)
{
    ListNode *pa = La->next, *pb = Lb->next, *pc = La, *q;
    La->next = NULL;
    while (pa && pb) {
        if (pa->elem < pb->elem) {
            q = pa;
            pa = pa->next;
            free(q);
        }
        else if (pa->elem > pb->elem)
            pb = pb->next;
        else {
            pc->next = pa;
            pc = pc->next;
            pa = pa->next;
            pb = pb->next;
            pc->next = NULL;
        }
    }
    while (pa) {
        q = pa;
        pa = pa->next;
        free(q);
    }
}
void testFindSharedStoreInA()
{
    int elems1[] = { 1,2,3,5,8,10,11 };
    ForwardList La = createListFromArray(elems1, sizeof(elems1) / sizeof(elems1[0]));
    int elems2[] = { 2,3,4,5,7,10,12 };
    ForwardList Lb = createListFromArray(elems2, sizeof(elems2) / sizeof(elems2[0]));

    puts("王道09：已知两个链表A和B分别表示两个集合，其元素递增排列。编制函数，求A与B的交集，并存放与A链表中。");
    printf("La=");
    printList(La);
    printf("\nLb=");
    printList(Lb);

    findSharedStoreInA(La, Lb);
    printf("\n公共元素为：\n");
    printf("La=");
    printList(La);

    DestroyList(&La);
    DestroyList(&Lb);

}

bool listIsSub(ForwardList La, ForwardList Lb)
{
    ListNode *pa = La->next, *pb = Lb->next, *pb_first = Lb->next;
    while (pa && pb) {
        if (pa->elem == pb->elem)
            pb = pb->next;
        else
            pb = pb_first;
        pa = pa->next;
    }
    return pb == NULL;
}
void testListIsSub()
{
    int elems1[] = { 5,1,9,42,1,2,10,8,1,2,3,4,5,1,2 };
    ForwardList La = createListFromArray(elems1, sizeof(elems1) / sizeof(elems1[0]));
    int elems2[] = { 1,2,3,4,5 };
    ForwardList Lb = createListFromArray(elems2, sizeof(elems2) / sizeof(elems2[0]));

    puts("王道10：两个整数序列A=a1,a2,a3,...,am和B=b1,b2,b3,...,bn已经存入两个单链表中，设计一个算法，判断序列B是否是A的连续子序列。");
    printList(Lb);
    printf("是否是 ");
    printList(La);
    printf("的连续子序列？ %d", listIsSub(La, Lb));

    DestroyList(&La);
    DestroyList(&Lb);
}

void linkCyclicList(CyclicNode* h1, CyclicNode* h2)
{
    if (!h2) return;
    CyclicNode* rear_h1 = h1;
    while (rear_h1->next != h1)
        rear_h1 = rear_h1->next;
    rear_h1->next = h2->next;
    h2->next = h1;
}

BiListNode* BiListLocate(BiList L, int data)
{
    BiListNode* p = L->next;
    while (p && p->data != data)
        p = p->next;
    // 结点值不存在
    if (!p) return NULL;
    // 增加访问频度
    ++p->freq;

    BiListNode* q = p->pre;
    if (q == L || q->freq > p->freq) // 不用移动
        return p;
    // 将p移动到freq相同结点的最前方
    q->next = p->next;
    if (p->next)
        p->next->pre = q;
    while (q != L && q->freq <= p->freq)
        q = q->pre;
    p->next = q->next;
    p->pre = q;
    q->next->pre = p;
    q->next = p; 
    return p;
}

void listRightShift(ListNode** node, int k)
{
    ListNode* first = *node, *pk = first, *p = first;
    for (int i = k; i > 0; --i)
        p = p->next;
    while (p->next) {
        pk = pk->next;
        p = p->next;
    }
    *node = pk->next;
    p->next = first;
    pk->next = NULL;
}
void testListRightShift()
{
    int elems[] = { 1,2,3,4,5,6,7,8,9 };
    ForwardList list = createListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
    puts("王道14：将链表循环右移k个位置。");
    printf("初始链表：");
    printList(list);

    int k = 4;
    listRightShift(&list->next, k);
    printf("\n循环右移%d位后：", k);
    printList(list);
    DestroyList(&list);
}

bool listRingExists(ForwardList list, ListNode** ringEntrance)
{
    ListNode *slow = list->next, *fast = slow;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        // 相遇
        if (fast == slow) break;
    }
    // 不存在环
    if (!fast || !fast->next) 
        return false;
    // 找环入口
    ListNode* first = list->next, *meet = slow;
    while (first != meet) {
        first = first->next;
        meet = meet->next;
    }
    *ringEntrance = meet;
    return true;
}
void testRingForCyclicList()
{
    puts("王道15：判断单链表是否有环。");
    int elems[] = { 1,2,3,4,5,6,7,8,9 };
    ForwardList list = createListFromArray(elems, sizeof(elems) / sizeof(elems[0]));

    // 弄成首尾相连
    ListNode* last = list->next;
    while (last->next)
        last = last->next;
    last->next = list->next;

    ListNode* ringEntrance;
    bool hasRing = listRingExists(list, &ringEntrance);
    printf("是否有环：%s", hasRing ? "是" : "否");
    if (hasRing)
        printf("\t环入口为：%d", ringEntrance->elem);

    last->next = NULL;
    DestroyList(&list);
}
void testListRingExists()
{
    puts("王道15：判断单链表是否有环。");
    int elems1[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
    ForwardList list = createListFromArray(elems1, sizeof(elems1) / sizeof(elems1[0]));
    ListNode* list1Last = list->next;
    while (list1Last->next)
        list1Last = list1Last->next;
    int elems2[] = { 13, 14, 15, 16 };
    ForwardList list2 = createListFromArray(elems2, sizeof(elems2) / sizeof(elems2[0]));
    ListNode* list2Last = list2->next;
    while (list2Last->next)
        list2Last = list2Last->next;
    
    // 链成环
    list1Last->next = list2->next;
    list2Last->next = list1Last;
    free(list2);

    ListNode* ringEntrance;
    bool hasRing = listRingExists(list, &ringEntrance);
    printf("是否有环：%s", hasRing ? "是" : "否");
    if (hasRing) {
        printf("\t环入口为：%d", ringEntrance->elem);
        // 断开环
        list2Last->next = NULL;
    }

    DestroyList(&list);
}

int twinSum(ListNode* head)
{
    ListNode *slow = head, *fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    // 将后半部分链表逆置，拆分成两个链表
    ListNode *p_latter = slow->next;
    slow->next = NULL;
    ListNode* p_insert;
    while (p_latter) {
        p_insert = p_latter;
        p_latter = p_latter->next;
        p_insert->next = slow->next;
        slow->next = p_insert;
    }
    ListNode *L2 = slow->next;
    slow->next = NULL;

    // 计算孪生和
    ListNode *p1 = head, *p2 = L2;
    int sum = p1->elem + p2->elem;
    while (p1 && p2) {
        if (sum < (p1->elem + p2->elem))
            sum = p1->elem + p2->elem;
        p1 = p1->next;
        p2 = p2->next;
    }
    // 把两个链表链接起来，方便回收内存空间
    slow->next = L2;
    return sum;
}

void testTwinSum()
{
    int elems[] = { 1,3,1,4,13,31,7,8,9,10 };
    ForwardList list = createListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
    puts("王道16：计算单链表的最大孪生和。");
    printf("初始链表：");
    printList(list);

    int sum = twinSum(list->next);
    printf("\n最大孪生和为：%d", sum);
    DestroyList(&list);
}

bool findListLastK(ListNode* head, int k, int* data)
{
    ListNode *p1 = head, *p2 = head;
    while (p2 && k > 1) {
        p2 = p2->next;
        --k;
    }
    if (!p2) return false;
    while (p2->next) {
        p1 = p1->next;
        p2 = p2->next;
    }
    *data = p1->elem;
    return true;
}
void testFindListLastK()
{
    int elems[] = { 1,2,3,4,5,6,7,8,9 };
    ForwardList list = createListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
    puts("王道17：查找链表中倒数第k个位置上的结点。");
    printf("初始链表：");
    printList(list);

    int k = 4;
    int data;
    findListLastK(list->next, k, &data);
    printf("\n倒数第%d个结点为：%d", k, data);
    DestroyList(&list);
}

ListNode* findSharedSuffix(ForwardList str1, ForwardList str2)
{
    ListNode* p1 = str1->next, * p2 = str2->next;
    int len1 = ListLength(str1);
    int len2 = ListLength(str2);
    // 将p1与p2对齐
    for (int i = 0; i < len1 - len2; ++i)
        p1 = p1->next;
    for (int i = 0; i < len2 - len1; ++i)
        p2 = p2->next;

    while (p1 && p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;
}

void testFindSharedSuffix()
{
    int elems_common[] = { 8,9,10 };
    ForwardList common = createListFromArray(elems_common, sizeof(elems_common) / sizeof(elems_common[0]));

    int elems1[] = { 20,19,18,17,16 };
    ForwardList La = createListFromArray(elems1, sizeof(elems1) / sizeof(elems1[0]));
    int elems2[] = { 15,14,13,12,11 };
    ForwardList Lb = createListFromArray(elems2, sizeof(elems2) / sizeof(elems2[0]));

    ListNode *rear1 = La, *rear2 = Lb;
    while (rear1->next)
        rear1 = rear1->next;
    while (rear2->next)
        rear2 = rear2->next;
    rear1->next = common->next;
    rear2->next = common->next;
    free(common);


    puts("王道18：找出由str1和str2所指向两个链表共同后缀的起始位置。");
    printf("La=");
    printList(La);
    printf("\nLb=");
    printList(Lb);

    ListNode *p = findSharedSuffix(La, Lb);
    printf("\n共同后缀的起始值为：%d", p->elem);

    rear2->next = NULL;
    DestroyList(&La);
    DestroyList(&Lb);
}

void listDeleteAbsDuplicates(ForwardList list, unsigned int n)
{
    int* arr = (int*)calloc(n + 1, sizeof(int));
    if (!arr) return;
    
    ListNode *pre = list, *p = list->next, *q;
    while (p) {
        if (arr[abs(p->elem)]) { // 删除重复的
            q = p;
            pre->next = p->next;
            p = p->next;
            free(q);
        }
        else {
            // |data|首次出现，设置为1
            arr[abs(p->elem)] = 1;
            pre = p;
            p = p->next;
        }
    }
    // 释放动态数组
    free(arr);
}

void testListDeleteAbsDuplicates()
{
    int elems[] = { 21,-15,-15,-7,15 };
    ForwardList list = createListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
    puts("王道19：保留第一次出现的结点而删除其余绝对值相等的结点。");
    printf("初始链表：");
    printList(list);
    
    listDeleteAbsDuplicates(list, 21);
    printf("\n删除绝对值相等的结点后，list=");
    printList(list);

    DestroyList(&list);

}

void rearrangeList(ForwardList list)
{
    ListNode *slow = list, *fast = list;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* L2_head = slow;

    // 将L2逆置
    ListNode* p2 = L2_head->next, *q;
    L2_head->next = NULL;
    while (p2) {
        q = p2;
        p2 = p2->next;
        q->next = L2_head->next;
        L2_head->next = q;
    }

    ListNode* L1 = list->next, *L1_next;
    ListNode* L2 = L2_head->next, *L2_next;
    // 断开L1和L2
    slow->next = NULL;

    while (L2) {
        L1_next = L1->next;
        L2_next = L2->next;
        L2->next = L1_next;
        L1->next = L2;
        L1 = L1_next;
        L2 = L2_next;
    }

}

void testRearrangeList()
{
    int elems[] = { 1,2,3,4,5,6,7,8,9,10 };
    ForwardList list = createListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
    puts("王道20：重排单链表。");
    printf("初始链表：");
    printList(list);

    rearrangeList(list);
    printf("\n重排后的链表：");
    printList(list);
    DestroyList(&list);
}

void splitOddEven(CyclicNode *A, CyclicNode *C)
{
    CyclicNode *odd_prev = A, *odd = A->next;
    CyclicNode* even = C;
    while (odd != A) {
        if (odd->data / 2 == 0) {
            odd_prev->next = odd->next;
            odd->next = NULL;
            even->next = odd;
            even = even->next;
            odd = odd_prev->next;
        }
    }
}

void deleteCyclicNodePrev(CyclicNode* p)
{
    // p前趋的前趋
    CyclicNode* prev = NULL;
    // p的前趋
    CyclicNode* node = p;
    while (node->next != p) {
        prev = node;
        node = node->next;
    }
    prev->next = p;
    free(node);
}

CyclicNode* sqListToCyclicList(const SqList *sqlist)
{
    CyclicNode* head = newCyclicNode(0);
    head->next = head;
    CyclicNode* rear = head;
    int data;
    for (int i = 1; i <= SqListLength(sqlist); ++i) {
        GetSqElem(sqlist, i, &data);
        CyclicNode *newNode = newCyclicNode(data);
        newNode->next = head;
        rear->next = newNode;
        rear = newNode;
    }
    return head;
}

CyclicNode* newCyclicNode(int data)
{
    CyclicNode* newNode = (CyclicNode*)malloc(sizeof(CyclicNode));
    if (!newNode) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


SqListArray* siftRepetition(ListNode* list)
{
    SqListArray* p_arr = (SqListArray*)malloc(sizeof(SqListArray));
    if (!p_arr) return NULL;

    // 初始化数组
    for (int i = 0; i < MAX_REPETITION; ++i)
        InitSqList(&(*p_arr)[i]);
        

    ListNode* p = list;
    while (p) {
        for (int i = 0; i < MAX_REPETITION; ++i) {
            SqList *sqlist = &(*p_arr)[i];
            SqElemType elem;
            if (SqListEmpty(sqlist)) {
                SqListInsert(sqlist, SqListLength(sqlist) + 1, p->elem);
                break;
            }
            else {
                GetSqElem(sqlist, SqListLength(sqlist), &elem);
                if (elem < p->elem) {// 当前遍历结点元素与当前顺序表最后一个元素进行比较
                    SqListInsert(sqlist, SqListLength(sqlist) + 1, p->elem);
                    break;
                }
            }
        }
        p = p->next;
    }
    return p_arr;
}

void testSiftRepetition()
{
    puts("分化。");
    int elems[] = { 1, 2 ,2, 3, 3 ,3, 4, 4, 5, 5, 6 };
    ForwardList list = createListFromArray(elems, sizeof(elems) / sizeof(int));
    SqListArray* p_arr = siftRepetition(list->next);

    // 打印结果
    for (int i = 0; i < MAX_REPETITION; ++i) {
        SqList* sqlist = &(*p_arr)[i];
        if (SqListEmpty(sqlist)) continue;
        SqElemType elem;
        for (int j = 1; j <= SqListLength(sqlist); ++j) {
            GetSqElem(sqlist, j, &elem);
            printf("%d ", elem);
        }
        printf("\n");
    }
    // 释放内存空间
    for (int i = 0; i < MAX_REPETITION; ++i) {
        SqList* sqlist = &(*p_arr)[i];
        DestroySqList(sqlist);
    }
    DestroyList(&list);
    free(p_arr);
}

bool isSymmetricList(ForwardList list)
{
    ListNode *slow, *fast;
    slow = fast = list->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    ListNode* p = slow;
    if (fast) {// 说明链表长度为奇数，此时slow指向正中间的结点
        p = p->next;
        puts("奇数");
    }

    ListNode* newListHead = (ListNode*)malloc(sizeof(ListNode));
    newListHead->next = NULL;

    ListNode* insertNode = NULL;
    while (p) {
        insertNode = (ListNode*)malloc(sizeof(ListNode));
        if (!insertNode) return false;
        insertNode->elem = p->elem;
        insertNode->next = newListHead->next;
        newListHead->next = insertNode;
        p = p->next;
    }

    // 比较
    ListNode* part1 = list->next;
    ListNode* part2 = newListHead->next;
    bool ret = true;
    while (part2) {
        if (part1->elem != part2->elem) {
            ret = false;
            break;
        }
        part1 = part1->next;
        part2 = part2->next;
    }
    // 回收内存空间
    DestroyList(&newListHead);
    return ret;
}

void testIsSymmetricList()
{
    puts("给你一个单链表的头结点head，请你判断该链表是否为回文链表。如果是，返回true；否则，返回false。");
    int elemsEven[] = { 1,2,3,3,2,1 };
    ForwardList listEven = createListFromArray(elemsEven, sizeof(elemsEven) / sizeof(int));
    printf("偶数个数，是否为回文链表？%d\n", isSymmetricList(listEven));

    int elemsOdd[] = { 1,2,3,4,3,2,1 };
    ForwardList listOdd = createListFromArray(elemsOdd, sizeof(elemsOdd) / sizeof(int));
    printf("奇数个数，是否为回文链表？%d\n", isSymmetricList(listOdd));

    DestroyList(&listEven);
    DestroyList(&listOdd);
}

ListNode* listMid(ForwardList list)
{
    ListNode *slow, *fast;
    slow = fast = list->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

void testListMid()
{
    puts("给定一个头结点为head的非空单链表，返回链表的中间结点。如果有两个中间结点，则返回第二个中间结点。");
    int elemsEven[] = { 1,2,3,3,2,1 };
    ForwardList listEven = createListFromArray(elemsEven, sizeof(elemsEven) / sizeof(int));
    printf("链表长度为偶数，中间结点值为：%d\n", listMid(listEven)->elem);

    int elemsOdd[] = { 1,2,3,4,3,2,1 };
    ForwardList listOdd = createListFromArray(elemsOdd, sizeof(elemsOdd) / sizeof(int));
    printf("链表长度为奇数，中间结点值为：%d\n", listMid(listOdd)->elem);

    DestroyList(&listEven);
    DestroyList(&listOdd);
}

ForwardList listSum(ListNode* L1, ListNode* L2)
{
    ListNode* sumList = newListNode(0);
    ListNode* sumListRear = sumList;

    if (L1->elem == 0)
        return L2;
    else if (L2->elem == 0)
        return L1;

    // 进位，0或1
    int overflow = 0;
    while (L1 && L2) {
        int sum = L1->elem + L2->elem + overflow;
        if (sum > 9) {
            sum = sum % 10;
            overflow = 1;
        }
        else {
            overflow = 0;
        }
        ListNode* newNode = newListNode(sum);
        sumListRear = sumListRear->next = newNode;
        L1 = L1->next;
        L2 = L2->next;
    }
    if (overflow) {
        if (L1) {
            ListNode* newNode = newListNode(L1->elem) + overflow;
            sumListRear = sumListRear->next = newNode;
            L1 = L1->next;
        }
        else if (L2) {
            ListNode* newNode = newListNode(L2->elem) + overflow;
            sumListRear = sumListRear->next = newNode;
            L2 = L2->next;
        }
        else {
            ListNode* newNode = newListNode(overflow);
            sumListRear = sumListRear->next = newNode;
        }
    }
    while (L1) {
        ListNode* newNode = newListNode(L1->elem);
        sumListRear = sumListRear->next = newNode;
        L1 = L1->next;
    }
    while (L2) {
        ListNode* newNode = newListNode(L2->elem);
        sumListRear = sumListRear->next = newNode;
        L2 = L2->next;
    }
    return sumList;
}

void testListSum()
{
    puts("链表求和。");

    int elems1[] = { 1,1 };
    ForwardList L1 = createListFromArray(elems1, sizeof(elems1) / sizeof(int));
    int elems2[] = { 9,8 };
    ForwardList L2 = createListFromArray(elems2, sizeof(elems2) / sizeof(int));

    ForwardList sum = listSum(L1->next, L2->next);

    printList(L1);
    printf("\n + \n");
    printList(L2);
    printf("\n = \n");
    printList(sum);

    DestroyList(&L1);
    DestroyList(&L2);
    DestroyList(&sum);
}

ListNode* deleteListDuplicates(ListNode* head)
{
    ListNode* prev = head;
    ListNode* p = head->next;
    ListNode* q = NULL;
    while (p) {
        if (p->elem == prev->elem) {
            q = p;
            prev->next = p->next;
            p = p->next;
            free(q);
        }
        else {
            prev = p;
            p = p->next;
        }
    }
    return head;
}

void testDeleteListDuplicates()
{
    puts("给定一个已排序的链表的头head，删除所有重复的元素，使每个元素只出现一次。返回已排序的链表。");
    int elems[] = { 1,1,2,3,3,4,4,5,5,5,6,7,7,8 };
    ForwardList list = createListFromArray(elems, sizeof(elems) / sizeof(int));

    deleteListDuplicates(list->next);

    printf("删除后重复元素后：");
    printList(list);

    DestroyList(&list);
}


