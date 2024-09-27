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
	int curPos = LocateSqElem(list, cur, sqElemEquals);
	// 未找到或是第一个元素
	if (curPos <= 1) return false;
	*pre = list->base[curPos - 2];
	return true;
}

bool NextSqElem(const SqList* list, const SqElemType cur, SqElemType* next)
{
	int curPos = LocateSqElem(list, cur, sqElemEquals);
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
		if (!LocateSqElem(La, elem, sqElemEquals))
			SqListInsert(La, ++La_length, elem);
	}
}

bool sqElemEquals(const SqElemType elem1, const SqElemType elem2)
{
	return elem1 == elem2;
}

void printSqElem(const SqElemType elem)
{
	printf("%d ", elem);
}

void printSqList(const SqList* list)
{
	if (!SqListEmpty(list))
		SqListTraverse(list, printSqElem);
}

SqList createSqListFromArray(const int arr[], int len)
{
	SqList list;
	InitSqList(&list);
	for (int i = 1; i <= len; ++i)
		SqListInsert(&list, i, arr[i - 1]);
	return list;
}

void testSqList()
{
	/*SqList list;
	InitSqList(&list);
	for (int i = 1; i <= 6; ++i)
		SqListInsert(&list, 1, i);
	printSqList(&list);
	printf("\n===============\n");

	SqElemType elem;
	SqListDelete(&list, 3, &elem);
	SqListDelete(&list, 3, &elem);
	printSqList(&list);

	SqList list2;
	InitSqList(&list2);
	SqListInsert(&list2, 1, 3);
	SqListInsert(&list2, 2, 4);
	UnionSqList(&list, &list2);

	printf("\n===============\n");
	printSqList(&list);

	DestroySqList(&list);
	DestroySqList(&list2);*/

	

	/*==========王道书第2章顺序表算法题测试=========*/

	//testDeleteMin();

	//testReverseSqList();

	//testDeleteX();

	//testDeleteRangeST();

	//testRemoveDuplicates();

	//testMergeSqList();

	//testExchangeTwoSqList();

	//testSearchAndUpdate();

	//testFindShared();

	//testFindMedian();

	//testFindMainElem();

	//testFindMinPositiveInt();

	//testMinDistanceOfTriTuple();

	//testNegativeBeforePositive();

	//testTransformSqlist();

	//testFindAbsent();

	//testPrintArrIntersection();

	//testPrintArrIntersection();

	testLostKInt();

}



/*==========王道书第2章顺序表算法题=========*/

int deleteMin(SqList* list)
{
	if (SqListEmpty(list)) return -1;
	int min = 0;
	for (int i = 0; i < list->length; ++i) 
		if (list->base[i] < list->base[min])
			min = i;
	int minVal = list->base[min];
	list->base[min] = list->base[list->length - 1];
	--list->length;
	return minVal;
}
void testDeleteMin()
{
	int elems[] = { 7,3,4,2,6,8,5 };
	SqList list = createSqListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
	printf("王道01：从顺序表中删除具有最小值的元素\n");
	printf("初始线性表：");
	printSqList(&list);
	int min = deleteMin(&list);
	printf("\n删除后：");
	printSqList(&list);
	DestroySqList(&list);
}

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
	int elems[] = { 1,2,3,4,5,6,7,8,9 };
	SqList list = createSqListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
	printf("王道02：设计一个高效算法，将顺序表L的所有元素逆置，要求算法的空间复杂度为O(1)\n");
	printf("初始线性表：");
	printSqList(&list);
	reverseSqList(&list);
	printf("\n逆置后：");
	printSqList(&list);
	DestroySqList(&list);
}

void deleteX(SqList* list, int x)
{
	if (SqListEmpty(list)) return;
	int* p = list->base;
	int* q = list->base + list->length - 1;
	while (p != q) {
		if (*p == x) {
			*p = *q;
			--q;
			--list->length;
		} else 
			++p;
	}
	// p == q，遍历到最后一个元素
	if (*p == x)
		--list->length;
}

void testDeleteX()
{
	int elems[] = { 1,2,3,9,4,9,5,9,9,6,7,8 };
	SqList list = createSqListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
	printf("王道03：删除顺序表中所有值为x的数据元素\n");
	printf("初始线性表：");
	printSqList(&list);

	deleteX(&list, 9);
	printf("\n删除9后：");
	printSqList(&list);
	DestroySqList(&list);
}

void deleteRangeST(SqList* list, int s, int t)
{
	if (SqListEmpty(list) || s >= t) return;
	int* p = list->base, *q = list->base + list->length - 1;
	while (p != q) {
		if (s <= *p && *p <= t) {
			*p = *q;
			--q;
			--list->length;
		} else
			++p;
	}
	// p == q
	if (s <= *p && *p <= t)
		--list->length;
}
void testDeleteRangeST()
{
	int elems[] = { 1,2,3,4,5,5,6,7,8 };
	SqList list = createSqListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
	printf("王道04：从顺序表中删除其值在给定值s和t之间（包含s和t，要求s<t）的所有元素\n");
	printf("初始线性表：");
	printSqList(&list);

	deleteRangeST(&list, 3, 5);
	printf("\n删除3到5后：");
	printSqList(&list);
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
	int elems[] = { 1,1,1,1,2,2,3,3,3,4,5,6,6,7,7,8,8,9,9 };
	SqList list = createSqListFromArray(elems, sizeof(elems) / sizeof(elems[0]));

	printf("王道05：从有序顺序表中删除所有其值重复的元素，使表中的元素均不同\n");
	printf("初始线性表：");
	printSqList(&list);
	removeDuplicates(&list);
	printf("\n删除重复元素后：");
	removeDuplicates(&list);
	printSqList(&list);
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
	int elems1[] = { 1,1,3,5,7,9 };
	SqList list1 = createSqListFromArray(elems1, sizeof(elems1) / sizeof(elems1[0]));
	int elems2[] = { 2,4,4,6,8,9,10 };
	SqList list2 = createSqListFromArray(elems2, sizeof(elems2) / sizeof(elems2[0]));
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
	int elems[] = { 1,2,3,4,5,6,7,8,9,10 };
	SqList list = createSqListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
	printf("王道07：将数组中两个顺序表的位置互换\n");
	printf("初始线性表：");
	printSqList(&list);
	exchangeTwoSqList(&list, 6, 4);
	printf("\n交换后：");
	printSqList(&list);
	DestroySqList(&list);
}

void searchAndUpdate(SqList* list, int x)
{
	if (SqListEmpty(list)) return;
	int* arr = list->base;
	int lo = 0, hi = list->length - 1;
	int mid = 0;
	while (lo <= hi) {
		mid = lo + (hi - lo) / 2;
		if (arr[mid] < x)
			lo = mid + 1;
		else if (arr[mid] > x)
			hi = mid - 1;
		else // 找到了
			break;
	}
	if (arr[mid] == x) {
		if (mid != list->length - 1) { // 不是最后一个元素才交换
			arr[mid] = arr[mid] + arr[mid + 1];
			arr[mid + 1] = arr[mid] - arr[mid + 1];
			arr[mid] = arr[mid] - arr[mid + 1];
		}
	} 
	// 没找到，插入
	else if (arr[mid] < x) 
		SqListInsert(list, mid + 2, x);
	else 
		SqListInsert(list, mid + 1, x);
}
void testSearchAndUpdate()
{
	int elems[] = { 1,2,3,4,5,6,7,8,9,10 };
	SqList list = createSqListFromArray(elems, sizeof(elems) / sizeof(elems[0]));
	printf("王道08：在表中查找数值为x的元素，若找到，则将其与后置元素位置相交换，若找不到，则将其插入表中并使表中元素仍递增有序\n");
	printf("初始线性表：");
	printSqList(&list);
	
	searchAndUpdate(&list, 11);
	printf("\n查找11，结果为：");
	printSqList(&list);
	searchAndUpdate(&list, 1);
	printf("\n查找1，结果为：");
	printSqList(&list);
	DestroySqList(&list);
}

SqList findShared(int A[], int B[], int C[], int n)
{
	SqList list;
	InitSqList(&list);

	int i = 0, j = 0, k = 0;
	while (i < n && j < n && k < n) {
		if (A[i] == B[j] && A[i] == C[k]) {
			SqListInsert(&list, list.length + 1, A[i]);
			++i;
			++j;
			++k;
		}
		else {
			if (A[i] < B[j] || A[i] < C[k])
				++i;
			else if (B[j] < A[i] || B[j] < C[k])
				++j;
			else // A[i] == B[j] && C[k]是最小的
				++k;
		}
	}
	return list;
}

void testFindShared()
{
	puts("王道09：给定三个序列A、B、C，长度均为n，且均为无重复元素的递增序列，找出同时存在于这三个序列中的所有元素");
	int A[] = { 1,2,3,5,8,10,11 };
	int B[] = { 2,3,4,5,7,10,12 };
	int C[] = { -1,0,2,4,5,10,11 };
	SqList list = findShared(A, B, C, 7);
	printf("共同元素为：");
	printSqList(&list);
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

int findMainElem(int A[], int n)
{
	int* B = (int*)calloc(n, sizeof(int));
	if (!B) return -1;
	for (int i = 0; i < n; ++i)
		++B[A[i]];
	for (int i = 0; i < n; ++i) {
		if (B[i] > n / 2) {
			free(B);
			return i;
		}
	}
	free(B);
	return -1;
}

void testFindMainElem()
{
	printf("王道12：找主元素\n");

	int A[] = { 0,5,5,3,5,7,5,5 };
	int n = sizeof(A) / sizeof(A[0]);
	printf("主元素为：%d\n", findMainElem(A, n));

	int B[] = { 0,5,5,3,5,1,5,7 };
	n = sizeof(B) / sizeof(B[0]);
	printf("主元素为：%d", findMainElem(B, n));
}

int findMinPositiveInt(int arr[], int n)
{
	// 数组排序 TODO

	int positiveInt = 1;
	for (int i = 0; i < n; ++i) {
		if (arr[i] < 1)
			continue;

		// 遍历到正整数了
		if (arr[i] > positiveInt)
			return positiveInt;
		else if (arr[i] == positiveInt)
			++positiveInt;
	}
	return positiveInt;
}

void testFindMinPositiveInt()
{
	puts("王道13：找出数组中未出现的最小正整数");
	int arr1[] = { -5,-1,0,1,2,3,3,3,4,6 };
	int n1 = sizeof(arr1) / sizeof(int);
	printf("arr1未出现的最小正整数是：%d\n", findMinPositiveInt(arr1, n1));
	int arr2[] = { 1,2,2,3,4,4,5,6,6,7,8 };
	int n2 = sizeof(arr2) / sizeof(int);
	printf("arr1未出现的最小正整数是：%d\n", findMinPositiveInt(arr2, n2));
}

void minDistanceOfTriTuple(int S1[], int len1, int S2[], int len2, int S3[], int len3, int result[])
{
	int D, Dmin = 0xffff;
	int i = 0, j = 0, k = 0;
	while (i < len1 && j < len2 && k < len3) {
		D = abs(S1[i] - S2[j]) + abs(S2[j] - S3[k]) + abs(S3[k] - S1[i]);
		if (D < Dmin) {
			Dmin = D;
			result[1] = S1[i];
			result[2] = S2[j];
			result[3] = S3[k];
		}
		if (S1[i] < S2[j] && S1[i] < S3[k])
			++i;
		else if (S2[j] < S1[i] && S2[j] < S3[k])
			++j;
		else
			++k;
	}
	result[0] = Dmin;
}

void testMinDistanceOfTriTuple()
{
	int ret[4] = { 0 };
	int S1[] = { -1,0,9 }, S2[] = { -25,-10,10,11 }, S3[] = { 2,9,17,30,41 };
	minDistanceOfTriTuple(S1, 3, S2, 4, S3, 5, ret);
	printf("三元组(%d,%d,%d)的距离为：%d\n", ret[1], ret[2], ret[3], ret[0]);
}


/*==========王道书第2章顺序表算法题=========*/

void negativeBeforePositive(int arr[], int len)
{
	int* begin = arr;
	int* end = arr + len - 1;
	while (begin < end) {
		if (*begin > 0) {
			while (begin < end && *end >= 0)
				--end;
			int temp = *begin;
			*begin = *end;
			*end = temp;
		}
		++begin;
	}
}

void testNegativeBeforePositive()
{
	puts("编写程序将一整数序列中所有负数移到所有正数之前，要求时间复杂度为O(n)。");
	int arr[] = { 1,-1,2,-2,3,-3,4,-4,5,6,-5,7 };
	int len = sizeof(arr) / sizeof(int);
	negativeBeforePositive(arr, len);
	printf("交换后序列为：");
	for (int i = 0; i < len; ++i)
		printf("%d ", arr[i]);
}

void transformSqlist(int arr[], int n)
{
	int m = n / 3;
	int temp;
	for (int i = 0; i < m; ++i) {
		temp = arr[i];
		arr[i] = arr[2 * m + i];
		arr[2 * m + i] = temp;
	}
	for (int i = m, j = 2 * m - 1; i < j; ++i, --j) {
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = arr[i];
	}
}
void testTransformSqlist()
{
	puts("改造顺序表");
	int arr[] = { 1,2,3,4,11,22,33,44,111,222,333,444 };
	int n = sizeof(arr) / sizeof(int);
	transformSqlist(arr, n);

	printf("改造后的顺序表：");
	for (int i = 0; i < n; ++i)
		printf("%d ", arr[i]);
}

int findAbsent(int nums[], int n)
{
	int* arr = (int*)calloc(n+1, sizeof(int));
	if (!arr) return -1;

	for (int i = 0; i < n; ++i) 
		arr[nums[i]] = 1;

	for (int i = 0; i <= n; ++i) 
		if (arr[i] == 0) {
			free(arr);
			return i;
		}
	return -1;
}

void testFindAbsent()
{
	puts("找出[0,n]没有出现的数。");
	int nums[] = {0,5,2,3,1};
	printf("未出现的数是：%d\n", findAbsent(nums, sizeof(nums) / sizeof(int)));

	int nums2[] = { 0,4,2,3,1 };
	printf("未出现的数是：%d\n", findAbsent(nums2, sizeof(nums2) / sizeof(int)));
}

void bubbleSortArr(int arr[], int n)
{
	for (int i = n-1; i > 0; --i) {
		for (int j = 0; j < i; ++j) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

SqList* printArrIntersection(int nums1[], int len1, int nums2[], int len2)
{
	bubbleSortArr(nums1, len1);
	bubbleSortArr(nums2, len2);

	SqList* sqlist = (SqList*)malloc(sizeof(SqList));
	if (!sqlist) return NULL;
	InitSqList(sqlist);
	int last = -1;
	for (int i = 0, j = 0; i < len1 && j < len2;) {
		if (nums1[i] < nums2[j])
			++i;
		else if (nums1[i] > nums2[j])
			++j;
		else {
			if (nums1[i] != last) {
				SqListInsert(sqlist, SqListLength(sqlist) + 1, nums1[i]);
				last = nums1[i];
			}
			++i;
			++j;
		}
	}
	return sqlist;
}

void testPrintArrIntersection()
{
	puts("给定两个数组nums1和nums2，返回它们的交集。输出结果中的每个元素一定是唯一的。我们可以不考虑输出结果的顺序。");
	int nums1[] = { 2,6,1,7,5,2,4,3,1,8 };
	int len1 = sizeof(nums1) / sizeof(int);

	int nums2[] = { 2,6,1,7,5,2,4,3,1,8,1,2,3 };
	int len2 = sizeof(nums2) / sizeof(int);

	SqList *sqlist = printArrIntersection(nums1, len1, nums2, len2);

	printf("nums1和nums2的交集为：");
	SqListTraverse(sqlist, printSqElem);

	DestroySqList(sqlist);
	free(sqlist);
}

int lostKInt(unsigned int arr[], int len, int k)
{
	int positiveInt = 0;
	int i = 0;
	while (i < len && k > 0) {
		++positiveInt;
		if (arr[i] == positiveInt) 
			++i;
		else 
			--k;
	}
	while (k > 0) { // 数组遍历完毕，还未找到第k个缺失的正整数
		++positiveInt;
		--k;
	}
	return positiveInt;
}

void testLostKInt()
{
	unsigned int arr[] = { 1,2,4,5,7,9 };
	int k = 3;
	printf("第%d个缺失的正整数为：%d\n", k, lostKInt(arr, sizeof(arr) / sizeof(unsigned int), k));
	k = 5;
	printf("第%d个缺失的正整数为：%d\n", k, lostKInt(arr, sizeof(arr) / sizeof(unsigned int), k));
}

biarray_ptr findIndicesTarget(int numbers[], int len, int target)
{
	biarray_ptr ptr = (biarray_ptr)malloc(sizeof(biarray));
	if (!ptr) return NULL;

	return ptr;
}

void testFindIndicesTarget()
{
}

