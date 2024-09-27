#ifndef BST_TREE_H_
#define BST_TREE_H_

#include "BiTree.h"

/*
 * 二叉排序树
 * date:2024/8/23
 */
typedef BiElemType BstElemType;
typedef BiNode BstNode, *BstTree;

void InitBstTree(BstTree* treePtr, BstElemType arr[], int length);

/* 
 * 递归方式插入
 */
void BstInsertRecur(BstTree* treePtr, BstElemType elem);

/*
 * 非递归方式插入
 */
void BstInsert(BstTree* treePtr, BstElemType elem);

/*
 * 递归方式删除
 */
void BstDeleteRecur(BstTree* bstTree, BstElemType elem);
void doBstDelete(BstNode** deletedNode);

/*
 * 非递归方式删除
 */
void BstDelete(BstTree* bstTree, BstElemType value);

static void testBstDelete();

void testBstTree();



/*==========电子科大7-5算法题=========*/

/*
*10、给定一个二叉搜索树，找到该树中两个指定结点的最近公共祖先。百度百科中最近公共祖先的定义为：“对于有根树T的两个结点p、q，最近公共祖先表示为一个结点x，满足x是p、q的祖先且x的深度尽可能大（一个结点也可以是它自己的祖先）。”
11、给你一个含重复值的二叉搜索树(BST)的根结点root，找出并返回BST中的所有众数（即，出现频率最高的元素）。如果树中有不止一个众数，可以按任意顺序返回。
12、给你一个二叉搜索树的根结点root，返回树中任意两不同结点值之间的最小差值。差值是一个正数，其数值等于两值之差的绝对值。
15、给你一个二叉搜索树的根结点root，返回树中任意两个不同结点值之间的最小差值。差值是一个正数，其数值等于两值之差的绝对值。
*/

/*==========电子科大7-5算法题end=========*/

#endif
