#include <iostream>
using namespace std;

class node
{
    public:
    int data;
    node *left;
    node *right;
    bool rightthread;

    node(int value)
    {
        data = value;
        left = right = nullptr;
        rightthread = false;
    }
};
class Queue
{
private:
    struct Node
    {
        node *data;
        Node *next;
    };
    Node *frontNode;
    Node *rearNode;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr) {}

    void push(node *value)
    {
        Node *newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;

        if (rearNode != nullptr)
        {
            rearNode->next = newNode;
        }
        else
        {
            frontNode = newNode;
        }
        rearNode = newNode;
    }

    void pop()
    {
        if (!isEmpty())
        {
            Node *temp = frontNode;
            frontNode = frontNode->next;
            if (!frontNode)
            {
                rearNode = nullptr;
            }
            delete temp;
        }
    }

    node *front()
    {
        if (frontNode != nullptr)
        {
            return frontNode->data;
        }
        else
        {
            return nullptr;
        }
    }

    bool isEmpty()
    {
        return frontNode == nullptr;
    }
};


node *addnodeTBT(node *root, int data)
{
    node *newnode = new node(data);
    if (root == nullptr)
    {
        root = newnode;
        return root;
    }
    Queue q;
    q.push(root);
    while (!q.isEmpty())
    {
        node *temp = q.front();
        q.pop();
        if (temp->left == nullptr)
        {
            temp->left = newnode;
            newnode->right = temp;
            newnode->rightthread = true;
            break;
        }
        else if (temp->right == nullptr || temp->rightthread)
        {
            newnode->right = temp->right;
            temp->right = newnode;
            newnode->rightthread = temp->rightthread;
            temp->rightthread = false;
            break;
        }
        else
        {
            if (temp->left != nullptr)
            {
                q.push(temp->left);
            }
            if (temp->right != nullptr && !temp->rightthread)
            {
                q.push(temp->right);
            }
        }
    }
    return root;
}

node *gotoleftmost(node *root)
{
    while (root != NULL && root->left != NULL)
    {
        root = root->left;
    }
    return root;
}
void inorderTBT(node *root)
{
    node *current = gotoleftmost(root);
    while (current != nullptr)
    {
        cout << current->data << " ";
        if (current->rightthread)
        {
            current = current->right;
        }
        else
        {
            current = gotoleftmost(current->right);
        }
    }
}

int getValidatedInt()
{
    int value;
    while (true)
    {
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a valid integer: ";
        }
        else
        {
            return value;
        }
    }
}

int main()
{
    node *root = nullptr;
    int choice;
    int node_value;

    do
    {
        cout << "\n--- Binary Tree Operations Menu ---\n";
        cout << "1. Insert Node\n";
        cout << "2. In-order Traversal\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        choice = getValidatedInt();

        switch (choice)
        {
        case 1:
            cout << "Enter the node value: ";
            node_value = getValidatedInt();
            root = addnodeTBT(root, node_value);
            cout << "Node inserted successfully.\n";
            break;

        case 2:
            if (root == nullptr)
            {
                cout << "The tree is empty. Please insert nodes first.\n";
            }
            else
            {
                cout << "In-order Traversal: ";
                inorderTBT(root);
                cout << endl;
            }
            break;

        case 3: // Exit
            cout << "Exiting program. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 3);

    return 0;
}