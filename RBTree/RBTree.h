#include <iostream>

#define bool int
#define true 1
#define false 0

enum Color { Red, Black };

struct rbnode
{
    int info;
    rbnode* left;
    rbnode* right;
    rbnode* parent;
    Color color;
};

typedef struct rbnode RBNode;

RBNode* bstRoot = NULL;

void Insert(int info);
RBNode* BstInsert(RBNode* x, RBNode* root);
void FixRedBlackTree(RBNode* x, RBNode* root);
void InorderTraversal(RBNode* root);
bool IsSiblingOfParentNullOrBlack(RBNode* x);
RBNode* GrandParent(RBNode* x);
void RotateRight(RBNode* x, bool flipColors);
void RotateLeft(RBNode* x, bool flipColors);
void ReColorFamily(RBNode* x);

RBNode* Find(int info);
void Delete(int info);