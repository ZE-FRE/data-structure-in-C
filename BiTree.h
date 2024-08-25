#ifndef  BITREE_H_
#define BITREE_H_

#include <stdbool.h>
#include "Queue.h"

/*
 * 二叉树
 * date:2024/8/22
 */

// 二叉树结点值类型
typedef int BiElemType;

typedef struct BiNode {
	// 结点元素值
	BiElemType elem;
	// 左子树
	struct BiNode* left;
	// 右子树
	struct BiNode* right;
	// 非递归后序遍历时，需要区分从左子树返回还是右子树返回，因此用此字段标记结点是否已访问。
	bool visited;
} BiNode, *BiTree;

// 访问二叉树结点函数
typedef void (*VisitBiNode)(BiNode* node);

// 构建树时，空结点占位符，#的ascii码值为35，因此测试创建二叉树时用不要用到35
#define PLACE_HOLDER '#'

/* 
 * 用先序序列[34,24,18,6,#,14,#,#,#,28,27,#,#,32,#,#,39,#,64,42,#,48,#,#,66,#,#]初始化为一棵二叉树
 *            34
 *          /    \
 *        24      39
 *      /   \       \
 *    18    28      64
 *   /     /  \    /  \
 *  6     27  32  42  66
 *   \              \
 *   14             48
 */
static BiTree createDefaultBiTree();

void InitBiTree(BiTree* bitree, BiElemType elems[], int len);

void InitBiTreeFromQueue(BiTree* bitree, Queue* queue);

// 新建二叉树结点
BiNode* newBiNode(BiElemType elem);

void DestroyBiTree(BiTree bitree);

/*
 * 递归遍历二叉树
 */
void PreOrderRecur(BiTree bstTree, VisitBiNode visit_func);
void InOrderRecur(BiTree bstTree, VisitBiNode visit_func);
void PostOrderRecur(BiTree bstTree, VisitBiNode visit_func);

/*
 * 非递归遍历二叉树
 */
void PreOrder(BiTree bitree, VisitBiNode visit_func);
void InOrder(BiTree bitree, VisitBiNode visit_func);
void PostOrder(BiTree bitree, VisitBiNode visit_func);

/*
 * 层序遍历
 */
void LevelOrder(BiTree bitree, VisitBiNode visit_func);

void printBiNode(BiNode* node);

static void testBiTreeTraverse();

void testBiTree();


/*==========王道书第5章二叉树算法题=========*/

/*
 * 04：试给出二叉树的自下而上、从右到左的层次遍历算法。
 * date:2024/8/25
 * 思路：题目所述的遍历顺序即为以层序遍历相反的顺序遍历，因此在层序遍历过程中，访问节点操作变为入栈，最后全部出栈遍历即可。
 */
void contraryLevelOrder(BiTree bitree);
void testContraryLevelOrder();

/*
 * 05：假设二叉树采用二叉链表存储结构，设计一个非递归算法求二叉树的高度。
 * date:2024/8/25
 * 思路：非递归后序遍历二叉树，二叉树的高度，即为遍历过程中，栈出现的最大长度时。
 */
int bitreeHeight(BiTree bitree);
void testBiTreeHeight();

/*
 * 
06：二叉树按二叉链表形式存储，试编写一个判别给定二叉树是否试完全二叉树的算法。
07：假设二叉树采用二叉链表存储结构存储，试设计一个算法，计算一棵给定二叉树的所有双分支结点个数。
08：设B是一棵采用链式结构存储的二叉树，编写一个把树B中所有结点的左、右子树进行交换的函数。
09：假设二叉树采用二叉链表存储结构存储，设计一个算法，求先序遍历序列中第k(1≤k≤二叉树中结点个数)个结点的值。
10：已知二叉树以二叉链表存储，编写算法完成：对于树中每个元素值为x的结点，删除以它为根的子树，并释放相应的空间。
11：在二叉树中查找值为x的结点，试编写算法（用C语言）打印值为x的结点的所有足先，假设值为x的结点不多于一个。
12：设一棵二叉树的结点结构为(LLINK,INFO,RLINK)，ROOT为指向该二叉树根结点的指针，p和q分别为指向该二叉树中任意两个结点的指针，试编写算法ANCESTOR(ROOT,p,q,r)，找到p和q的最近公共祖先结点r。
13：假设二叉树采用二叉链表存储结构，设计一个算法，求非空二叉树b的宽度（即具有结点数最多的那一层的结点个数）。
14：设有一棵满二叉树（所有结点值均不同），已知其先序序列为pre，设计一个算法求其后序序列post。
15：设计一个算法将二叉树的叶结点按从左到右的顺序练成一个单链表，表头指针为head。二叉树按二叉链表方式存储，链接时用叶结点的右指针域来存放单链表指针。
16：试设计判断两棵二叉树是否相似的算法。所谓二叉树T1和T2相似，指的是T1和T2都是空的二叉树或都只有一个根结点；或者T1的左子树和T2的左子树是相似的，且T1的右子树和T2的右子树是相似的。
17【2014统考真题】二叉树的带权路径长度（WPL）是二叉树中所有叶结点的带权路径长度之和。给定一棵二叉树T，采用二叉链表存储，结点结构为 left  weight  right，其中叶结点的weight域保存该结点的非负权值。设root为指向T的根结点的指针，请设计求T的WPL的算法。
 */

/*
 * 18【2017统考真题】请设计一个算法，将给定的表达式树（二叉树）转换为等价的中缀表达式（通过括号反映操作符的计算次序）并输出。
 * 例如，当下列两棵表达式树作为算法的输入时：
 *			 *							+
 *		/         \					/  		\
 *	   +		   *			   *		 -
 *	 /   \		 /   \			 /	 \		  \
 *  a	  b	    c	  -		    a	  b		   -
 *						\					 /	 \
 *						 d					c	  d
 * 输出的等价中缀表达式分别为(a+b) * (c*(-d))和(a*b) + (-(c-d))。
 * 二叉树结点定义如下：
 */
typedef struct node {
	char data[10];
	struct node *left, *right;
} BTree;

/*
 * 19【2022统考真题】已知非空二叉树T的结点值均为正整数，采用顺序存储方式保存，数据结构定义如下：
 */
#define MAX_SIZE 10
typedef struct {			 // MAX_SIZE为已定义常量
	int SqBiTNode[MAX_SIZE]; // 保存二叉树结点值的数组
	int ElemNum;			 // 实际占用的数组元素个数
} SqBiTree;
/*
 * T中不存在的结点在数组SqBiTNode中用-1表示。例如，对于下图所示的两棵非空二叉树T1和T2，
 *			40						40
 *		/ 		 \				/		\
 *	   25		  60		  50		60
 *		 \		    \			\
 *		  30		 80			 30
 *		  /						   \
 *		27							35
 *			二叉树T1					二叉树T2
 * T1的存储结果如下：
 * T1.SqBiTNode  40 25 60 -1 30 -1 80 -1 -1 27 空 空
 * T1.ElemNum=10
 * T2的存储结果如下：
 * T2.SqBiTNode  40 50 60 -1 30 -1 -1 -1 -1 -1 35 空
 * T2.ElemNum=11
 * 请设计一个尽可能高效的算法，判定一棵采用这种方式存储的二叉树是否为二叉搜索树，若是，则返回true，否则，返回false。
 */


/*==========王道书第5章二叉树算法题=========*/

#endif

