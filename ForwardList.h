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

void printList(const ForwardList list);

ForwardList createListFromArray(const int arr[], int len);

void testForwardList();


/*==========王道书第2章链表算法题=========*/

/*
* 01：在带头结点的单链表L中，删除所有值为x的结点，并释放其空间，假设值为x的结点不唯一，试编写算法以实现上述操作。
* date:2024/8/5
*/ 
void listDeleteElem(ForwardList list, ListElemType elem);
void testListDeleteElem();

/*
 * 02：试编写在带头结点的单链表L中删除一个最小值结点的高效算法（假设该结点唯一）。
 * date:2024/8/7
 */
void listDeleteMin(ForwardList list);
void testListDeleteMin();

/*
 * 03：试编写算法将带头结点的单链表就地逆置，所谓“就地”是指辅助空间复杂度为O(1)。
 * date:2024/8/7
 */
void reverseList(ForwardList list);
void testReverseList();

/*
 * 04：设在一个带表头结点的单链表中，所有结点的元素值无序，试编写一个函数，删除表中所有介于给定的两个值（作为函数参数给出）之间的元素（若存在）。
 * date:2024/8/7
 */
void listDeleteRange(ForwardList list, int s, int t);
void testListDeleteRange();

/*
 * 05：给定两个单链表，试分析找出两个链表的公共结点的思想（不用写代码）。
 */

/*
 * 06：设C={a1,b1,a2,b2,...,an,bn}为线性表，采用带头结点的单链表存放，设计一个就地算法，
 * 将其拆分为两个线性表，使得A={a1,a2,...,an}，B={bn,...,b2,b1}。
 * date:2024/8/7
 * 思路：用La与Lb保存拆分的两个链表，用pca遍历链表Lc，pcb指向pca的下一个结点，遍历过程中，
 * 用尾插法把pca插入La，用头插法把pcb插入Lb，然后pca向后移动两步，当pca为NULL时遍历完毕。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */
void separateList(ForwardList Lc, ForwardList* La, ForwardList* Lb);
void testSeparateList();

/*
 * 07：在一个递增有序的单链表中，存在重复的元素。设计算法删除重复的元素。
 * 例如(7,10,10,21,30,42,42,51,70)将变为(7,10,21,31,42,51,70)。
 * date:2024/7/7
 * 思路：与04几乎一致，只是判断条件不一样
 */
void listDeleteDuplicates(ForwardList list);
void testListDeleteDuplicates();

/*
 * 08：设A和B是两个单链表（带头结点），其中元素递增有序。设计一个算法从A和B中的公共元素产生链表C，要求不破坏A、B的结点。
 * date:2024/8/7
 */
ForwardList findListShared(ForwardList La, ForwardList Lb);
void testFindListShared();
/*
 * 09：已知两个链表A和B分别表示两个集合，其元素递增排列。编制函数，求A与B的交集，并存放与A链表中。
 * date:2024/8/8
 */
void findSharedStoreInA(ForwardList La, ForwardList Lb);
void testFindSharedStoreInA();


/*
 * 10：两个整数序列A=a1,a2,a3,...,am和B=b1,b2,b3,...,bn已经存入两个单链表中，设计一个算法，判断序列B是否是A的连续子序列。
 * date:2024/8/8
 */
bool listIsSub(ForwardList La, ForwardList Lb);
void testListIsSub();

/*
 * 14：设将n(n>1)个整数存放到不带头结点的单链表L中，设计算法将L中保存的序列循环右移k(0<k<n)个位置。
 * 例如，若k=1，则将链表{0,1,2,3}变为1{3,0,1,2}。给出算法的基本设计思想，说明时间、空间复杂度。
 * date:2024/8/8
 * 思路：设两个指针pk和p，初始时pk指向第一个结点，p指向第k+1个结点，即pk和p的距离为k，向后移动这两个指针，当p->next为NULL时，
 * pk就指向倒数第k-1个结点。此时只需将pk后的k个结点移动到链表头即可。具体操作为：p->next=第一个结点，pk->next=NULL;
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */
void listRightShift(ListNode **node, int k);
void testListRightShift();

/*
 * 15：单链表有环，是指单链表的最后一个结点的指针指向了链表中的某个结点（通常单链表的最后一个结点的指针域是空的）。
 * 试编写算法判断单链表是否存在环。给出算法的基本设计思想，说明时间、空间复杂度。
 * date:2024/8/9
 * 思路：用快慢指针，slow每次向后移动一步，fast每次向后移动两步，当fast追上slow时，表明存在环。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 * 
 * 第一个结点到环入口的长度为a  ▽环入口	   16->next == 12
 * 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16  设环长度为r
 *								 ▲设这里为相遇点，环入口到相遇点的距离为x
 * 则要是能求出a或者r-x的值，即可确定环的入口
 * 以fast指针走过的距离为切入点列方程。
 * 设当slow==fast时，fast已绕环n圈，则fast指针走过的距离为：a+nr+x，也等于slow走的距离乘以2，即有以下方程：
 * a+nr+x = 2(a+x) => a = nr - x = (n-1)r + r-x
 * 因此只要设两个指针，一个指向第一个结点，一个指向相遇点，每次向后走一步，当两指针相遇时，即为环入口。
 */
bool listRingExists(ForwardList list, ListNode **ringEntrance);
void testRingForCyclicList();
void testListRingExists();

/*
 * 16：设有一个长度为n(n为偶数)的不带头结点的单链表，且结点值都大于0，设计算法求这个单链表的最大孪生和。
 * 孪生和定义为一个结点值与其孪生结点值之和，对于第i个结点（从0开始），其孪生结点为第n-i-1个结点。
 * date:2024/8/9
 */
int twinSum(ListNode* head);
void testTwinSum();

/*
 * 17【2009统考真题】：已知一个带有头结点的单链表，假设该链表只给出了头指针list。
 * 在不改变链表的前提下，请设计一个尽可能高效的算法，查找链表中倒数第k个位置上的结点（k为正整数）。
 * 若查找成功，算法输出该结点的data域的值，并返回1；否则，只返回0。
 * date:2024/8/9
 * 思路：用两个指针p1和p2，两指针的距离为k-1，开始时p1指向头指针，p2指向p1 k-1个位置后的结点，
 * 若p2为NULL，则表示k不合理，返回0；
 * 向后移动p1和p2，当p2指向最后一个结点时，p1指向倒数第k个结点。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */
bool findListLastK(ListNode* head, int k, int* data);
void testFindListLastK();

/*
 * 18【2012统考真题】：假定带头结点的单链表保存单词，当两个单词有相同的后缀时，可共享相同的后缀存储空间，
 * 例如，loading和being的存储映像如下图所示。
 * head->l o a d   
 * 			    i n g
 * head->b e
 * 设str1和str2分别指向两个单词所在单链表的头结点，链表结点结构为 data | next，请设计一个时间上尽可能高效的算法，
 * 找出由str1和str2所指向两个链表共同后缀的起始位置（如图中字符i所在结点的位置p）。
 */

/*

11：设计一个算法用于判断带头结点的循环双链表是否对称。
12：有两个循环单链表，链表头指针分别为h1和h2，编写一个函数将链表h2链接到链表h1之后，要求链接后的链表仍保持循环链表形式。
13：设有一个带头结点的非循环双链表L，其每个结点中除有pre、data和next域外，还有一个访问频度freq，其值均初始化为零。每当在链表中进行一次Locate(L,x)运算时，令值为x的结点中freq域的值增1，并使此链表中的结点保持按访问频度递减的顺序排列，且最近访问的结点排在频度相同的结点之前，以便使频繁访问的结点总是靠近表头。试编写符合上述要求的Locate(L,x)函数，返回找到结点的地址，类型为指针型。

19【2015统考真题】：用单链表保存m个整数，结点的结构为[data][link]，且|data|≤n(n为正整数)。
现要求设计一个时间复杂度尽可能高效的算法，对于链表中data的绝对值相等的结点，仅保留第一次出现的结点而删除其余绝对值相等的结点。
例如，若给定的单链表head如下：
head 21 -15 -15 -7 15
head 21 -15 -7

20【2019统考真题】：设线性表L=(a1,a2,a3,...,an-2,an-1,an)采用带头结点的单链表保存，
请设计一个空间复杂度为O(1)且时间上尽可能高效的算法，重新排列L中的各结点，得到线性L'=(a1,an,a2,an-1,a3,an-2,...)。
*/


/*==========王道书第2章链表算法题=========*/

#endif

