#include <iostream>
#include <queue>
#include <stack>
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

    queue<node *> q;
    q.push(root);
    while (!q.empty())
    {
        node *temp = q.front();
        q.pop();

        if (temp->left == NULL)
        {
            temp->left = createnode(data);
            break;
        }
        else
        {
            q.push(temp->left);
        }

        
        if (temp->right == NULL)
        {
            temp->right = createnode(data);
            break;
        }
        else
        {
            q.push(temp->right);
        }
    }
    return root;
}
void depthfirst(node *root)
{
    if (root == NULL)
    {
        return;
    }
    stack<node *> s;
    s.push(root);
    while (!s.empty())
    {
        node *current = s.top();
        s.pop();
        cout << current->data << " ";

        if (current->right)
        {
            s.push(current->right);
        }
        if (current->left)
        {
            s.push(current->left);
        }
    }
}
void postorder(node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

int main()
{
    node *root = NULL; 

    int flag = 0;
    int nodeval;

    cout << "Enter the value for the root node: ";
    cin >> nodeval;
    root = insertnode(root, nodeval); 
    while (flag != 1)
    {
        cout << "Enter the node value: ";
        cin >> nodeval;
        root = insertnode(root, nodeval); 
        cout << "To continue entering nodes enter 0, to finish enter 1: ";
        cin >> flag;
    }

    cout << "Your PostOrder traversal: ";
    postorder(root);
    cout << "Your depth FIrst search:  ";
    depthfirst(root);
    cout << endl;

    return 0;
}
