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

void BstDelete(BstTree* bstTree, BstElemType value);

static void testBstDelete();

void testBstTree();

#endif
