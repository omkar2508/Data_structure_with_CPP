#include <iostream>
using namespace std;

struct node
{
    int data;
    node *left;
    node *right;
};

node *creteBT(int data)
{
    node *newnode = new node();
    newnode->data = data;
    newnode->left = newnode->right = NULL;
    return newnode;
}

int main()
{
    node *root = creteBT(10);
    cout << "Tree created with root value: " << root->data << endl;
    return 0;
}