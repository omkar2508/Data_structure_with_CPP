#include <iostream>
using namespace std;

struct node
{
    int data;
    node *left;
    node *right;
};

node *cretenode(int data)
{
    node *newnode = new node();
    newnode->data = data;
    newnode->left = newnode->right = NULL;
    return newnode;
}
node *insertnode(node *root, int data)
{
    if (root == NULL)
    {
        root = cretenode(data);
        return root;
    }
    if (data < root->data)
    {
        root->left = insertnode(root->left, data);
    }
    else
    {
        root->right = insertnode(root->right, data);
    }
    return root;
}
int main()
{
    node *root = NULL;
    root = insertnode(root, 50);
    root = insertnode(root, 30);
    root = insertnode(root, 49);
    root = insertnode(root, 60);
    cout << "Nodes added to the tree!" << endl;
    return 0;
}
