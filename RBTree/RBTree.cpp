#include <iostream>
#include <stdlib.h>
#include "RBTree.h"
using namespace std;

RBNode* GrandParent(RBNode* x)
{
    return x->parent->parent;
}

bool IsSiblingOfParentNullOrBlack(RBNode* x)
{
    if (GrandParent(x)->left == x->parent)
    {
        return GrandParent(x)->right == NULL || GrandParent(x)->right->color == Black;
    }
    else
    {
        return GrandParent(x)->left == NULL || GrandParent(x)->left->color == Black;
    }
}

RBNode* BstInsert(RBNode* x, RBNode* root)
{
    if (root == NULL)
    {
        root = x;
    }
    else if (x->info >= root->info)
    {
        root->right = BstInsert(x, root->right);
        root->right->parent = root;
    }
    else
    {
        root->left = BstInsert(x, root->left);
        root->left->parent = root;
    }

    return root;
}

void ReColorFamily(RBNode* x)
{
    if (x->parent != NULL)
    {
        x->color = Red;
    }
    x->left->color = Black;
    x->right->color = Black;
}

void RotateLeft(RBNode* x, bool flipColors)
{
    RBNode* y = x->parent;

    x->parent = y->parent;
    if (y->parent == NULL)
    {
        x->parent = NULL;
        bstRoot = x;
    }
    else if (y->parent->left == y)
    {
        x->parent->left = x;
    }
    else
    {
        x->parent->right = x;
    }

    y->right = x->left;
    if (x->left != NULL)
    {
        x->left->parent = y;
    }
    y->parent = x;
    x->left = y;

    if (flipColors)
    {
        y->color = Red;
        x->color = Black;
    }
}

void RotateRight(RBNode* x, bool flipColors)
{
    RBNode* y = x->parent;

    x->parent = y->parent;
    if (y->parent == NULL)
    {
        x->parent = NULL;
        bstRoot = x;
    }
    else if (y->parent->left == y)
    {
        x->parent->left = x;
    }
    else
    {
        x->parent->right = x;
    }

    y->left = x->right;
    if (x->right != NULL)
    {
        x->right->parent = y;
    }
    y->parent = x;
    x->right = y;
    if (flipColors)
    {
        y->color = Red;
        x->color = Black;
    }
}

void FixRedBlackTree(RBNode* x, RBNode* root)
{
    if (x == root)
    {
        root->color = Black;
        return;
    }

    if (x->parent->color == Black) { return; }
    //Red-red parent child
    if (IsSiblingOfParentNullOrBlack(x) == true)
    {
        if (x == x->parent->left && x->parent == GrandParent(x)->left)
        {
            RotateRight(x->parent, true);
        }
        else if (x == x->parent->right && x->parent == GrandParent(x)->right)
        {
            RotateLeft(x->parent,true);
        }
        else if (x == x->parent->left && x->parent == GrandParent(x)->right)
        {
            RotateRight(x, false);
            RotateLeft(x, true);
        }
        else if (x == x->parent->right && x->parent == GrandParent(x)->left)
        {
            RotateLeft(x, false);
            RotateRight(x, true);
        }
    }
    else
    {
        ReColorFamily(GrandParent(x));
        FixRedBlackTree(GrandParent(x), bstRoot);
    }
}


void Insert(int info)
{
    RBNode* newNode = new RBNode;
    newNode->info = info;
    newNode->left = newNode->right = newNode->parent = NULL;
    newNode->color = Red;

    bstRoot = BstInsert(newNode, bstRoot);

    FixRedBlackTree(newNode, bstRoot);

    InorderTraversal(bstRoot);
    cout << "\n";
}

void InorderTraversal(RBNode* node)
{
    if (node == NULL) { return; }
    InorderTraversal(node->left);
    cout << node->info << " ";
    InorderTraversal(node->right);
}

RBNode* Find(int info)
{
    auto p = bstRoot;
    int found = 0;
    while (p != NULL && found == 0)
    {
        if (p->info == info)
            found = 1;
        if (found == 0)
        {
            if (p->info < info)
                p = p->right;
            else
                p = p->left;
        }
    }
    return p;
}

/*BNode* getSuccessor(RBNode* node)
{
    auto successorParent = node;
    auto successor = node;
    auto current = node->right;

    while (current != NULL)
    {
        successorParent = successor;
        successor = current;
        current = current->left;
    }

    if (successor != node->right)
    {
        successorParent->left = current->right;
        successor->right = node->right;
    }

    return successor;
}

void deleteChildCase(RBNode* delNode)
{
    if (delNode->right == NULL && delNode->left == NULL)
    {
        if (delNode == bstRoot)
            bstRoot = NULL;
        else if (delNode == delNode->parent->left)
            delNode->parent->left = NULL;
        else
            delNode->parent->right = NULL;
    }
}
*/
void Delete(int info)
{
    auto check = Find(info);

    if (check != NULL)
    {
        //auto successor = getSuccessor(check);
        deleteCase(check);
    }
    cout << "Deleted"; 
    InorderTraversal(bstRoot);
    cout << "\n";
}

int main()
{
    Insert(8);
    Insert(18);
    Insert(5);
    Insert(15);
    Insert(17);
    Insert(25);
    Insert(40);
    Insert(80);

    auto x = Find(80);
    if (x != NULL)
    {
        cout << "Found";
    }
    else
    {
        cout << "Not Found";
    }

    Delete(80);
}