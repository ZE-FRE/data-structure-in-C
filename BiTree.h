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
 * 思路：遍历二叉树，二叉树的高度，即为遍历过程中，栈出现的最大长度。
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



 /*==========电子科大算法题真题=========*/

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

/*
 *【2020真题2】一个二叉排序树中，如何寻找结点值小于x且是所有满足该条件的结点中值最大的结点？
 * date:2024/9/20
 * 思路：题目意思为找结点值为x的结点在中序下的直接前驱。则只需在中序遍历时，记录直接前驱，当遍历结点值为x时，返回true。
 */
bool directPrevInOrder(BiTree bitree, BiNode** prev, BiElemType x);
void testDirectPrevInOrder();

/*
 * 【2021真题2】判断二叉树的对称性：判断二叉树是否关于根结点呈镜像对称，只要求结构对称，不要求数值也对称，是返回1，否则返回0。
 * 参考函数原型：int IsSymmetricTree(BiTreeNode *root)
 * date:2024/9/20
 * 思路：从根结点下的左、右孩子开始，判断对称条件为：left->left与right->right都存在或都不存在，
 * 以及left->right与right->left都存在或都不存在。
 */
bool isSymmetricTree(BiTree root);
bool doIsSymmetricTree(BiNode* left, BiNode* right);
void testIsSymmetricTree();

/*
 *【2022真题2】给了二叉树的数据结构，判断是否为平衡二叉树。
 * date:2024/9/23
 * 思路：后序遍历二叉树，分别判断左、右子树是否为平衡二叉树，同时计算左、右子树的高度。
 */
bool isAVLTree(BiTree bitree, int* height);
void testIsAVLTree();

/*==========电子科大算法题真题end=========*/



/*==========电子科大7-5算法题=========*/

/*
 * 1、给定一个二叉树的根结点root，返回它的中序遍历。
 */

/*
 * 2、给你两棵二叉树的根结点p和q，编写一个函数来检验这两棵树是否相同。
 * 如果两棵树在结构上相同，并且结点具有相同的值，则认为它们是相同的。
 * date:2024/9/25
 * 思路：先序遍历
 * 若p和q都为空，返回true；
 * 若p和q一个为空，一个不为空，则返回false；
 * 若p和q都不为空，结点值不同返回false，若结点值相同，则再遍历左子树、右子树
 */
bool BiTreeEquals(BiTree T1, BiTree T2);
void testBiTreeEquals();

/*
 * 3、给你一个二叉树的根结点root，检查它是否轴对称。
 * date:2024/9/25
 * 思路：类似【2021真题2】，但在结构对称的基础上，此题要求结点值也对称。
 */
void testBiTreeSymmetry();

/*
 * 4、给定一棵二叉树，找出其最大深度。二叉树的深度为根结点到最远叶子结点的最长路径上的结点树。
 * date:2024/9/25
 */
void bitreeDepth(BiTree bitree, int currHeight, int *height);
void testBiTreeDepth();

/*
 * 5、给你一个整数数组nums，其中元素已经按升序排序，请你将其转换为一棵高度平衡二叉搜索树。
 * 高度平衡二叉树是一棵满足 每个结点的左右两个子树的高度差的绝对值不超过1的二叉树。
 */

/*
 * 6、给定一棵二叉树，判断它是否是高度平衡的二叉树。
 * 本题中，一棵高度平衡二叉树定义为：一个二叉树结点的左右两个子树的高度差的绝对值不超过1。
 * date:2024/9/25
 * 同【2022真题2】
 */

/*
 * 7、给定一个二叉树，找出其最小深度。最小深度是从根结点到最近叶子结点的最短路径上的结点数量。
 * date:2024/9/25
 * 思路：后序遍历二叉树
 */
int BiTreeMinDepth(BiTree bitree);
void testBiTreeMinDepth();

/*
 * 8、给你二叉树的根结点root和一个表示目标和的整数targetSum。判断该树中是否存在根结点到叶子结点的路径，
 * 这条路径上的所有结点值相加等于目标和 targetSum。如果存在，返回true；否则，返回false。
 * date:2024/9/25
 * 思路：先序遍历
 */
bool existsTargetSum(BiTree bitree, int prevSum, int targetSum);
void testExistsTargetSum();

/*
 * 9、给你一棵二叉树的根结点root，翻转这颗二叉树，并返回其根结点。
 *[leetcode：https://leetcode.cn.problems/invert-binary-tree/]
 * 已做过
 */

/*
 *13、给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。
 * 这条路径可能穿过也可能不穿过根结点。
 * date:2024/9/26
 * 思路：后序遍历，从底向上依次计算每个结点作为根结点的子树的直径长度，取左、右子树、当前结点直径长度的最大值，即为当前结点的直径长度。
 * 
 * param: height：当前树的高度
 * return: 当前树的直径长度
 */
int BiTreeDiameter(BiTree bitree, int* height);
void testBiTreeDiameter();

/*
 * 14、给你一个二叉树的根结点root，计算并返回整个树的坡度。
 * 一个树的结点的坡度定义即为，该结点左子树的结点之和和右子树结点之和的差的绝对值。
 * 如果没有左子树的话，左子树的结点之和为0；没有右子树的话也是一样。空结点的坡度是0。整个树的坡度就是其所有结点的坡度之和。
 * date:2024/9/25
 * 思路：后序遍历二叉树
 */
int BiTreeSlope(BiTree bitree, int *nodeCount);
void testBiTreeSlope();

/*==========电子科大7-5算法题end=========*/

#endif

