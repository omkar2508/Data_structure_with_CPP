#include <iostream>
using namespace std;

struct node
{
    int data;
    node *left;
    node *right;
};

node *createnode(int data)
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
        root = createnode(data);
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

node *modifynode(node *root, int olddata, int newdata)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->data == olddata)
    {
        root->data = newdata;
    }
    else if (olddata < root->data)
    {
        root->left = modifynode(root->left, olddata, newdata);
    }
    else
    {
        root->right = modifynode(root->right, olddata, newdata);
    }
    return root;
}

int main()
{
    node *root = NULL;
    root = insertnode(root, 50);
    root = insertnode(root, 30);

    root = insertnode(root, 20);
    root = insertnode(root, 20);
    root = modifynode(root, 20, 25);

    cout << "Node modified!" << endl;

    return 0;
}
