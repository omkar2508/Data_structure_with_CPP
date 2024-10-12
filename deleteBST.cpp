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
        return createnode(data);
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
node *deletenode(node *root, int data)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (data < root->data)
    {
        root->left = deletenode(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = deletenode(root->right, data);
    }
    else
    {
        // case 1:No child
        if (root->left == NULL && root->right == NULL)
        {
            return NULL;
        }
        // case 2: one child in left
        else if (root->left != NULL)
        {
            node *temp = root;
            root = root->left;
            delete temp;
        }
        // case 3:one child in right
        else if (root->right != NULL)
        {
            node *temp = root;
            root = root->right;
            delete temp;
        }
        // case 4: two child
        else if (root->left != NULL && root->right != NULL)
        {
            node *temp = root->right;
            while (temp->left != NULL)
            {
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = deletenode(root->right, temp->data);
        }
    }
    return root;
}
int main()
{
    node *root = NULL;
    root = insertnode(root, 50);
    root = insertnode(root, 30);
    root = insertnode(root, 20);
    root = insertnode(root, 70);
    root = insertnode(root, 60);
    root = insertnode(root, 80);

    root = deletenode(root, 20); // Delete node with value 20
    cout << "Node deleted!" << endl;

    return 0;
}