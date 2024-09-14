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

// 构建树时，空结点占位符，#的ascii码值为35，因此测试创建二叉树时不要用到35
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

void printBiNodeAsChar(BiNode* node);

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
 * 思路：非递归后序遍历二叉树，二叉树的高度，即为遍历过程中，栈出现的最大长度。
 */
int bitreeHeight(BiTree bitree);
void testBiTreeHeight();

/*
 * 06：二叉树按二叉链表形式存储，试编写一个判别给定二叉树是否是完全二叉树的算法。
 * date:2024/8/29
 * 思路：完全二叉树按层序编号，序号从1~n应该是与满二叉树一一对应的，因此按层序遍历二叉树（空指针也入队），
 * 若二叉树是完全二叉树，则当遍历到第一个空结点(NULL)时，说明二叉树已遍历完毕，队列中的剩余元素应该全是NULL，
 * 因此，当遍历到空结点时，若队列中还有非空结点，则该二叉树不是完全二叉树。
 * ★
 * 看了答案才做出来
 */
bool isCompleteBitree(BiTree bitree);
void testIsCompleteBitree();

/*
 * 07：假设二叉树采用二叉链表存储结构存储，试设计一个算法，计算一棵给定二叉树的所有双分支结点个数。
 * date:2024/8/26
 * 思路一：定义一个全局变量表示二叉树双分支结点个数，在遍历二叉树过程中（先序、中序、后序、层序，递归/非递归都可以），
 * 判断当前结点左右子树是否都存在，若存在，则双分支结点树+1，遍历完毕时全局变量的值即为二叉树双分支结点个数。
 * 思路二：后序递归遍历二叉树，函数返回二叉树双分支结点个数，遍历过程中，先遍历左子树得到左子树的双分支结点个数，
 * 再遍历右子树得到右子树的双分支结点个数，然后判断当前结点是否是双分支结点（左右子树都存在），若是，
 * 则返回左、右子树双分支结点个数之和 + 1，否则只返回左、右子树双分支结点个数之和。
 * 时间复杂度：O(n)
 * 空间复杂度：O(二叉树高度)，最坏情况下二叉树退化为链表，这是空间复杂度为O(n)
 */
int doubleNodeCount(BiTree bitree);
void testDoubleNodeCount();

/*
 * 08：设B是一棵采用链式结构存储的二叉树，编写一个把树B中所有结点的左、右子树进行交换的函数。
 * date:2024/8/26
 * 思路：先序或后序递归遍历二叉树（中序不行），遍历过程中交换结点的左、右子树
 */
void swapLeftRight(BiTree bitree);
void testSwapLeftRight();

/*
 * 09：假设二叉树采用二叉链表存储结构存储，设计一个算法，求先序遍历序列中第k(1≤k≤二叉树中结点个数)个结点的值。
 * date:2024/8/27
 * 思路：先序遍历过程中，用count计数，当count == k时，即找到了第k个结点值；
 * 若二叉树遍历完时，count < k，则表明二叉树结点数小于k。
 */
static int pre_k = 5, k_count = 0;
// 递归方式
BiElemType kValueOnPreOrderRecur(BiTree bitree);
// 非递归方式，查找成功返回true，kValue为第k个结点值，查找失败返回false
bool kValueOnPreOrder(BiTree bitree, int k, BiElemType *kValue);
void testKValueOnPreOrder();

/*
 * 10：已知二叉树以二叉链表存储，编写算法完成：对于树中每个元素值为x的结点，删除以它为根的子树，并释放相应的空间。
 * date:2024/8/27
 */
void deleteSubTree(BiTree *bitree, BiElemType deletedX);
void testDeleteSubTree();

/*
 * 11：在二叉树中查找值为x的结点，试编写算法（用C语言）打印值为x的结点的所有祖先，假设值为x的结点不多于一个。
 * date:2024/8/27
 */
bool printAncestors(BiTree bitree, BiElemType x);
void testPrintAncestors();

/*
 * 12：设一棵二叉树的结点结构为(LLINK,INFO,RLINK)，ROOT为指向该二叉树根结点的指针，
 * p和q分别为指向该二叉树中任意两个结点的指针，试编写算法ANCESTOR(ROOT,p,q,r)，找到p和q的最近公共祖先结点r。
 * 
 */
bool ANCESTOR(BiTree ROOT, BiNode* p, BiNode* q, BiNode** r);
void testANCESTOR();

/*
 * 13：假设二叉树采用二叉链表存储结构，设计一个算法，求非空二叉树b的宽度（即具有结点数最多的那一层的结点个数）。
 * date:2024/8/28
 * 思路：先序遍历二叉树过程中，记录当前遍历结点的层数，用count_arr数组记录每层结点数，数组下标为层数，若当前结点不为空，
 * 则当前层数的结点数+1。遍历完二叉树后，count_arr数组中的最大值，即为二叉树的宽度。
 * 时间复杂度：求二叉树高度要遍历一次二叉树，统计没层结点数又要遍历一次二叉树，找count_arr数组最大值，执行次数二叉树高度，
 * 综上：最坏情况下，执行次数为3n，时间复杂度为O(n)
 * 空间复杂度：O(n)
 */
int bitreeWidth(BiTree bitree);
// 遍历二叉树，统计每层结点个数，node为当前遍历结点，level为当前结点的层数，count_arr为每层结点个数
void increaseWidth(BiNode* node, int level, int count_arr[]);
void testBitreeWidth();

/*
 * 14：设有一棵满二叉树（所有结点值均不同），已知其先序序列为pre，设计一个算法求其后序序列post。
 * date:2024/8/30
 * 思路：
 */
void fullBiTreePreToPost(int pre[], int pre_begin, int pre_end, int post[], int post_end);
void testFullBiTreePreToPost();

/*
 * 15：设计一个算法将二叉树的叶结点按从左到右的顺序链成一个单链表，表头指针为head。
 * 二叉树按二叉链表方式存储，链接时用叶结点的右指针域来存放单链表指针。
 * date:2024/28
 * 思路：先序遍历二叉树，函数参数附设一个指针指向上一个叶子结点，遍历过程中，若当前结点是叶子结点，
 * 则把当前结点链接到上一个叶子结点的右指针域，上一个叶子结点变为当前结点。
 */
void linkLeaf(BiTree bitree, BiNode** preLeaf);
void testLinkLeaf();

/*
 * 16：试设计判断两棵二叉树是否相似的算法。所谓二叉树T1和T2相似，指的是T1和T2都是空的二叉树或都只有一个根结点；
 * 或者T1的左子树和T2的左子树是相似的，且T1的右子树和T2的右子树是相似的。
 * date:2024/8/28
 * 思路：
 */
bool bitreeSimilarity(BiTree T1, BiTree T2);
void testBitreeSimilarity();

/*
 * 17【2014统考真题】二叉树的带权路径长度（WPL）是二叉树中所有叶结点的带权路径长度之和。给定一棵二叉树T，
 * 采用二叉链表存储，结点结构为 left  weight  right，其中叶结点的weight域保存该结点的非负权值。
 * 设root为指向T的根结点的指针，请设计求T的WPL的算法。
 * date:2024/8/28
 */
int bitreeWPL(BiTree root, int level);
void testBitreeWPL();

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
 * date:2024/8/29 
 */
void printExpression(BiTree bitree);
void testPrintExpression();

/*
 * 19【2022统考真题】已知非空二叉树T的结点值均为正整数，采用顺序存储方式保存，数据结构定义如下：
 */
#define MAX_SIZE 30
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
/*
 * date:2024/8/29
 */
bool SqBiTreeIsBST(SqBiTree *bitree);
void InitSqBiTree(SqBiTree* bitree, int elems[], int len);
void testSqBiTreeIsBST();


/*==========王道书第5章二叉树算法题=========*/


/*
 * 【2007真题2】设二叉树采用二叉链表存储，结点结构为lchild、data和rchild，试编写输出二叉树中从根结点到每个叶结点的路径的算法。
 * 设二叉树最长路径结点个数小于m，可以使用队列S[1:m]，初始时S.rear=S.front=1。
 * date:2024/9/13
 * 思路：先序非递归遍历二叉树，当遍历到叶子结点时，栈中结点就是此叶子结点的所有祖先，打印栈中结点与当前叶子结点，就是从根结点到每个叶结点的路径。
 */

/*
 * 【2012真题】如果以二叉链表作为存储结构，试用类C语言编写统计二叉树非叶子结点个数的层次遍历算法。
 */
int branchCount(BiTree bitree);
void testBranchCount();

/*
 * 【2015真题2】采用二叉链表的存储结构，用非递归算法（pop(s,t)，push(s,t)）交换二叉树的左右子树。
 * date:2024/9/14
 */
void exchangeLeftRight(BiNode* node);
void testExchangeLeftRight();

/*
 * 【2016真题2】二叉树用二叉链表结构进行存储。请编写算法求二叉树根结点左右子树相隔最远的叶子结点之间距离。
 * date:2024/9/14
 * 思路：等价于求根结点左右子树各自的高度，最远距离即为左右子树高度之和。
 */
int leafLongestDistance(BiTree bitree);
void testLeafLongestDistance();

/*
 * 【2017真题2】二叉树用二叉链表结构进行存储，设计一个算法交换二叉树的左右子树。
 * date:2024/9/14
 * 递归和非递归的，上面都实现了。
 */

/*
 * 【2018真题2】对于两棵给定的二叉树A和B，判断B是不是A的子结构（约定空树不是任意一个树的子结构）。
 * B是A的子结构，即A中出现和B相同的结构和结点值。
 * 
 * 思路：先序遍历二叉树A，先找到与B根结点值相同的结点，然后比较两棵树是否相同，若相同，则返回true，否则继续遍历A，
 * 若A遍历完毕，则返回false。
 */
bool bitreeIsEqual(BiTree T1, BiTree T2);
bool isSubTree(BiTree A, BiTree B);
void testIsSubTree();


/*
 * leetcode:114. 二叉树展开为链表
 * 展开后的单链表应该同样使用二叉树结点，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
 * date:2024/9/14
 * 思路：展开，就是在遍历过程中把左子树最后一个结点作为右子树的根结点，右子树指针域指向左子树指针域
 */
BiNode* bitreeExpandToList(BiNode* root);
void testBitreeExpandToList();

#endif

