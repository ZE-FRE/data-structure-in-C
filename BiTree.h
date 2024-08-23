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

// 构建树时，空结点占位符
#define PLACE_HOLDER '#'
// #的ascii码值为35，因此测试创建二叉树时用不要用到35
/* 
 * 用先序数组初始化二叉树，如用数组[34,24,18,6,#,14,#,#,#,28,27,#,#,32,#,#,39,#,64,42,#,48,#,#,66,#,#]
 * 初始化为如下一棵二叉树
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


#endif

