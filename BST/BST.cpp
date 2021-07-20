#include <iostream>

using namespace std;

struct TNode
{
    int data;
    TNode* left;
    TNode* right;
};

class BST
{
public:
    BST()
    {
        root = nullptr;
    }

    void insert(const int& value)
    {
        auto newTNode = new TNode;
        auto cur = root;
        auto parent = cur;
        while (cur != nullptr)
        {
            parent = cur;
            if (value < cur->data)
            {
                cur = cur->left;
            }
            else if (value > cur->data)
            {
                cur = cur->right;
            }
            else
            {
                cout << "Value already exists." << endl;
                return;
            }
        }
        newTNode->data = value;
        newTNode->left = newTNode->right = nullptr;
        cur = newTNode;
        if (root == nullptr)
        {
            root = cur;
        }
        else if (value < parent->data)
        {
            parent->left = cur;
        }
        else
        {
            parent->right = cur;
        }
    }

    void traversal()
    {
        cout << "Inorder Traversal: " << endl;
        inOrder(root);
        cout << endl;
    }

    void inOrder(TNode* root)
    {
        if (root == nullptr)
        {
            return;
        }
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }

    void searchTree(int data)
    {
        search(root, data);
    }

    void search(TNode* root, const int& data)
    {
        if (root->data == data)
        {
            cout << "Found" << endl;
        }
        else if (data < root->data)
        {
            search(root->left, data);
        }
        else if (data > root->data)
        {
            search(root->right, data);
        }
        else
        {
            cout << "Not Found" << endl;
        }
    }

private:
    TNode* root;
};

int main()
{
    BST t;
    t.insert(5);
    t.insert(6);
    t.insert(4);
    t.insert(7);
    t.traversal();
    t.searchTree(7);
}