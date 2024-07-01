#ifndef BST_TREE_H_

typedef struct BstNode {

	int value;
	struct BstNode* left;
	struct BstNode* right;

} BstNode, *BstTree;

BstNode* NewNode(int value);

void Init(BstTree* treePtr, int arr[], int length);

void Add(BstTree* treePtr, int value);

void InOrder(BstTree bstTree, void (*funcptr)(BstNode *node));


void Destroy(BstTree bstTree);

static void print(BstNode* node);

void testBstTree();

#endif
