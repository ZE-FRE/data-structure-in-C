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

void printSqList(const SqList* list);

SqList createSqListFromArray(const int arr[], int len);

void testSqList();



/*==========王道书第2章顺序表算法题=========*/

/*
 * 01：从顺序表中删除具有最小值的元素(假设唯一)并由函数返回被删除的元素。空出的位置由最后一个元素填补。
 * 若顺序表为空，则显示出错信息并退出运行。
 * date:2024/7/29
 */
int deleteMin(SqList* list);
void testDeleteMin();

/*
 * 02：设计一个高效算法，将顺序表L的所有元素逆置，要求算法的空间复杂度为O(1)
 * date:2024/7/26
 * 思路：双指针，一个指向头，一个指向尾，向中间靠近，p1 >= p2时退出循环
 */
void reverseSqList(SqList *list);
void testReverseSqList();

/*
 * 03：对长度为n的顺序表L，编写一个时间复杂度为O(n)、空间复杂度为O(1)的的算法，该算法删除顺序表中所有值为x的数据元素。
 * date:2024/7/29
 * 思路：采用双指针，p初始指向第一个元素，用于遍历顺序表，q指向最后一个元素，用于替换被删除元素，
 * 当p所指向的元素等于x(即*p==x)，则用最后一个元素(即q所指元素)替换，当p==q时，表示已遍历到最后一个元素
 */
void deleteX(SqList* list, int x);
void testDeleteX();

/*
 * 04：从顺序表中删除其值在给定值s和t之间（包含s和t，要求s<t）的所有元素，若s或t不合理或顺序表为空，则显示出错信息并退出运行。
 * date:2024/7/29
 * 思路：在上一题的基础上，把判断条件改为s<=*p<=t即可。另注：当s==t时退化为上一题
 */
void deleteRangeST(SqList* list, int s, int t);
void testDeleteRangeST();

/* 
 * 05：从有序顺序表中删除所有其值重复的元素，使表中的元素均不同
 * date:2024/7/25
 * 思路：采用双指针，insert初始指向顺序表头，用于插入元素，p用于遍历顺序表，将p所指的值插入到insert处，当*p == *(p+1)时，不插入
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
 * 08：线性表(a1,a2,a3,...,an)中的元素递增有序且按顺序存储于计算机内。要求设计一个算法，完成用最少时间在表中查找数值为x的元素，
 * 若找到，则将其与后置元素位置相交换，若找不到，则将其插入表中并使表中元素仍递增有序。
 * date:2024/7/29
 * 思路：采用二分查找，查找成功：arr[mid] == x，查找失败：lo > hi
 */
void searchAndUpdate(SqList* list, int x);
void testSearchAndUpdate();

/*
 * 09：给定三个序列A、B、C，长度均为n，且均为无重复元素的递增序列，请设计一个时间上尽可能高效的算法，
 * 逐行输出同时存在于这三个序列中的所有元素。例如，数组A为{1,2,3}，数组B为{2,3,4}，数组C为{-1,0,2}，则输出2。
 * date:2024/7/30
 * 思路：设置三个整数下标来遍历三个数组，若当前三个数组下标位置的值都相等，则记录，三个数组下标都向后移动，
 * 否则值小的那个数组下标向后移动。当任一个数组遍历完毕时，算法执行完毕。
 * 时间复杂度：最坏情况下，执行次数为3n，所以复杂度为O(n)
 * 空间复杂度：只打印的情况下，复杂度为O(1)
 */
SqList findShared(int A[], int B[], int C[], int n);
void testFindShared();

/*
 * 10【2010统考真题】：设将n(n>1)个整数存放到一维数组R中。设计一个在时间和空间两方面都尽可能高效的算法。
 * 将R中保存的序列循环左移p(0<p<n)个位置，即将R中的数据由(X0,X1,...,Xn-1)变换为(Xp,Xp+1,...,Xn-1,X0,X1,..,Xp-1)。
 * date:2024/7/30
 * 思路：等价于将数组元素循环右移n-p个位置，同07题。
 */
 
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

/*
 * 12(2013统考真题)：已知一个整数序列A=(a0,a1,...,an-1)，其中0≤ai<n(0≤i<n)。若存在ap1=ap2=...=apm=x且m>n/2(0≤pk<n,1≤k≤m),
 * 则称x为A的主元素。例如A=(0,5,5,3,5,7,5,5)，则5为主元素；又如A=(0,5,5,3,5,1,5,7)，则A中没有主元素。
 * 假如A中的n个元素保存在一个一维数组中，请设计一个尽可能高效的算法，找出A的主元素。若存在主元素，则输出该元素，否则输出-1。
 * date:2024/7/29
 * 思路：初始化一个长度为n，值全为0的辅助数组B，数组下标k表示元素值k，B[k]的值表示k出现的次数，
 * 首先遍历序列A，将B[k]的值进行++操作；然后遍历数组B，当B[k] > n/2时，k就是序列A的主元素。
 * 时间复杂度为O(n)
 * 空间复杂度为O(n)
 */
int findMainElem(int A[], int n);
void testFindMainElem();

/*
 * 13(2018统考真题)：给定一个含n(n≥1)个整数的数组，请设计一个在时间上尽可能高效的算法，找出数组中未出现的最小正整数。
 * 例如：数组{-5,3,2,3}中未出现的最小正整数是1；数组{1,2,3}中未出现的最小正整数是4。
 * date:2024/7/29
 * 思路：先将数组递增排序；然后令正整数postiveInt=1，遍历数组，从第一个非负数开始，依次与positiveInt进行比较，
 * 若当前数组下标对应的值大于positiveInt(小于则说明数组中有重复元素，只移动数组下标)，则数组中未出现的最小正整数即为positiveInt，
 * 否则，遍历下一个元素，positiveInt++
 */
int findMinPositiveInt(int arr[], int n);
void testFindMinPositiveInt();

/*
 * 14【2020统考真题】：定义三元组(a,b,c)(a,b,c均为整数)的距离D=|a-b|+|b-c|+|c-a|。
 * 给定3个非空整数集合S1、S2和S3，按升序分别存储在3个数组中。
 * 请设计一个尽可能高效的算法，计算并输出所有可能的三元组(a,b,c)(a∈S1,B∈S2,C∈S3)中的最小距离。
 * 例如S1={-1,0,9}，S2={-25,-10,10,11}，S3={2,9,17,30,41}，则最小距离为2，相应的三元组为(9,10,9)。
 * date:2024/8/2
 * 
 * 分析：a,b,c是三个数，则用数轴来演示
 * 不妨设a < b < c，数轴表示如下：
 * a    b      c，则三元组(a,b,c)的距离D=2|c-a|，可以看出D与a到b的距离，以及b到c的距离无关，所以在设计算法时，
 * 不需要关心|a-b|是不是最小，|b-c|是不是最小，只需要关心|c-a|是不是最小，但不能直接算|c-a|，因为a与c的大小关系假设的。
 * 直接计算D=|a-b|+|b-c|+|c-a|取即可。
 * 算法思路：
 * ① 分别用下标i、j、k遍历数组S1、S2和S3，计算D，若D < Dmin，则Dmin = D
 * ② 移动下标，从数轴上可看出，只要移动a、b、c中值最小的数组下标，D就变小了，但新的a可能 > b 且 > c，有可能导致D变大，由第一步，则Dmin保持不变
 * ③ 算法结束条件：任一数组遍历完毕
 * 时间复杂度：设三个数组总长度为n，则为O(n)
 * 空间复杂度：O(1)
 */
void minDistanceOfTriTuple(int S1[], int len1, int S2[], int len2, int S3[], int len3, int result[]);
void testMinDistanceOfTriTuple();


/*==========王道书第2章顺序表算法题=========*/


/*
 * 【2005真题1】编写程序将一整数序列中所有负数移到所有正数之前，要求时间复杂度为O(n)。
 * date:2024/9/6
 * 思路：用指针begin从前往后遍历序列，end从后往前遍历序列，当begin位置的值为负数时，向后移动，为正数时，切换到end，
 * end向前遍历，遇到负数时，交换begin与end的位置的值，又切换到begin继续遍历。当begin >= end时，算法结束。
 */
void negativeBeforePositive(int arr[], int len);
void testNegativeBeforePositive();

#endif
