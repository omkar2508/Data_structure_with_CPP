#include <iostream>
#include <limits>
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
    newnode->left = newnode->right = nullptr;
    return newnode;
}

class Stack
{
private:
    struct Node
    {
        node *data; // representing a binary tree node
        Node *next; // used for the stack or queue
    };
    Node *topNode;

public:
    Stack() : topNode(nullptr) {}

    void push(node *value)
    {
        Node *newNode = new Node;
        newNode->data = value;
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop()
    {
        if (!isEmpty())
        {
            Node *temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    node *top()
    {

        if (topNode != nullptr)
        {
            return topNode->data;
        }
        else
        {
            return nullptr;
        }
    }

    bool isEmpty()
    {
        return topNode == nullptr;
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

node *insertBT(node *root, int value)
{
    node *newNode = createnode(value);
    if (root == nullptr)
    {
        root = newNode;
    }
    else
    {
        Queue q;
        q.push(root);

        while (!q.isEmpty())
        {
            node *temp = q.front();
            q.pop();

            if (temp->left == nullptr)
            {
                temp->left = newNode;
                return root;
            }
            else if (temp->right == nullptr)
            {
                temp->right = newNode;
                return root;
            }
            else
            {
                q.push(temp->left);
                q.push(temp->right);
            }
        }
    }
    return root;
}

node *searchNode(node *root, int target)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    Queue q;
    q.push(root);
    while (!q.isEmpty())
    {
        node *temp = q.front();
        q.pop();

        if (temp->data == target)
        {
            return temp;
        }

        if (temp->left != nullptr)
        {
            q.push(temp->left);
        }
        if (temp->right != nullptr)
        {
            q.push(temp->right);
        }
    }
    return nullptr;
}
node *bottom(node *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    node *parent = nullptr;
    Queue q;
    q.push(root);
    while (!q.isEmpty())
    {
        node *current = q.front();
        q.pop();
        if (current->left)
        {
            parent = current;
            q.push(current->left);
        }
        if (current->right)
        {
            q.push(current->right);
            parent = current;
        }
    }
    return parent;
}
void deleteNode(node *&root, int value)
{
    node *nodeToDelete = searchNode(root, value);
    if (nodeToDelete == nullptr)
        return;

    node *b_parent = bottom(root);
    if (b_parent == nullptr)
    {
        root = nullptr;
        return;
    }
    else
    {
        if (b_parent->right)
        {
            node *temp = b_parent->right;
            nodeToDelete->data = b_parent->right->data;
            b_parent->right = nullptr;
            delete temp;
        }
        else
        {
            node *temp = b_parent->left;
            nodeToDelete->data = b_parent->left->data;
            b_parent->left = nullptr;
            delete temp;
        }
    }
    return;
}

void preorder(node *root)
{
    if (root == nullptr)
    {
        return;
    }

    Stack s;
    s.push(root);
    node *lastvisited = nullptr;
    node *current;

    while (!s.isEmpty())
    {
        current = s.top();
        s.pop();
 
        if (current->left != nullptr && current->left != lastvisited && current->right != lastvisited)
        {
            cout << current->data << " ";
            s.push(current);
            s.push(current->left);
        }
        else if (current->right != nullptr && current->right != lastvisited)
        {
            s.push(current);
            s.push(current->right);
        }
        else if (current->left == nullptr && current->right == nullptr)
        {
            cout << current->data << " ";
        }

        lastvisited = current;
    }
}
void postorder(node *root)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        Stack s;
        s.push(root);
        node *lastvisited = nullptr;
        node *current;

        while (!s.isEmpty())
        {
            current = s.top();
            s.pop();
            if (current->left != nullptr && current->left != lastvisited && current->right != lastvisited)
            {
                s.push(current);
                s.push(current->left);
            }
            else if (current->right != nullptr && current->right != lastvisited)
            {
                s.push(current);
                s.push(current->right);
            }
            else
            {
                cout << current->data << " ";
            }
            lastvisited = current;
        }
    }
}
void inorder(node *root)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        Stack s;
        s.push(root);
        node *lastvisited = nullptr;
        node *current;
        while (!s.isEmpty())
        {
            current = s.top();
            s.pop();
            if (current->left != nullptr && current->left != lastvisited && current->right != lastvisited)
            {
                s.push(current);
                s.push(current->left);
            }
            else if (current->right != nullptr && current->right != lastvisited)
            {
                cout << current->data << " ";
                s.push(current);
                s.push(current->right);
            }
            else if (current->right == nullptr)
            {
                cout << current->data << " ";
            }
            lastvisited = current;
        }
    }
}

void BFS(node *root)
{
    if (root == nullptr)
    {
        return;
    }

    Queue q;
    q.push(root);
    while (!q.isEmpty())
    {
        node *temp = q.front();
        q.pop();
        cout << temp->data << " ";
        if (temp->left)
        {
            q.push(temp->left);
        }
        if (temp->right)
        {
            q.push(temp->right);
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
        cout << "\n--- Binary Search Tree Operations Menu ---\n";
        cout << "1. Insert Node\n";
        cout << "2. Post-order Traversal\n";
        cout << "3. In-order Traversal\n";
        cout << "4. Pre-order Traversal\n";
        cout << "5. Breadth-First Search (BFS)\n";
        cout << "6. Delete Node\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        choice = getValidatedInt();

        switch (choice)
        {
        case 1:
            cout << "Enter the node value: ";
            node_value = getValidatedInt();
            root = insertBT(root, node_value);
            cout << "Node inserted successfully.\n";
            break;

        case 2:
            if (root == nullptr)
            {
                cout << "The tree is empty. Please insert nodes first.\n";
            }
            else
            {
                cout << "Post-order Traversal: ";
                postorder(root);
                cout << endl;
            }
            break;

        case 3:
            if (root == nullptr)
            {
                cout << "The tree is empty. Please insert nodes first.\n";
            }
            else
            {
                cout << "In-order Traversal: ";
                inorder(root);
                cout << endl;
            }
            break;

        case 4:
            if (root == nullptr)
            {
                cout << "The tree is empty. Please insert nodes first.\n";
            }
            else
            {
                cout << "Pre-order Traversal: ";
                preorder(root);
                cout << endl;
            }
            break;

        
        case 5:
            if (root == nullptr)
            {
                cout << "The tree is empty. Please insert nodes first.\n";
            }
            else
            {
                cout << "Breadth-First Search (BFS): ";
                BFS(root);
                cout << endl;
            }
            break;

        case 6:
            if (root == nullptr)
            {
                cout << "The tree is empty. Please insert nodes first.\n";
            }
            else
            {
                cout << "Enter the value to delete: ";
                node_value=getValidatedInt();
                deleteNode(root, node_value);
                cout << "Node deleted successfully.\n";
            }
            break;

        case 7: // Exit
            cout << "Exiting program. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 7);

    return 0;
}