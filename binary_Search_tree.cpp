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

node *insertnode(node *root, int data)
{
    if (root == NULL)
    {
        root = createnode(data);
        return root;
    }
    if (data <= root->data)
    {
        root->left = insertnode(root->left, data);
    }
    else
    {
        root->right = insertnode(root->right, data);
    }
    return root;
}

node *minVal(node *root)
{
    while (root->left != nullptr)
    {
        root = root->left;
    }
    return root; // Return the node with the minimum value
}

node *deleteFromBst(node *root, int val)
{
    if (root == NULL)
    {
        return root; // Base case: If the tree is empty
    }

    // Traverse the tree to find the node to delete
    if (val < root->data)
    {
        root->left = deleteFromBst(root->left, val);
    }
    else if (val > root->data)
    {
        root->right = deleteFromBst(root->right, val);
    }
    else
    {
        // Node to be deleted is found

        // Case 1: Node with no children (leaf node)
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }

        // Case 2: Node with one child (left or right)
        if (root->left != NULL && root->right == NULL)
        {
            node *temp = root->left;
            delete root;
            return temp;
        }
        if (root->left == NULL && root->right != NULL)
        {
            node *temp = root->right;
            delete root;
            return temp;
        }

        // Case 3: Node with two children
        if (root->left != NULL && root->right != NULL)
        {
            // Find the in-order successor (minimum value in the right subtree)
            node *successor = minVal(root->right);
            root->data = successor->data; // Replace the value
            root->right = deleteFromBst(root->right, successor->data); // Delete the successor
        }
    }
    return root;
}

void BFS(node *root)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        Queue q;
        q.push(root);
        while (!q.isEmpty())
        {
            node *current = q.front();
            q.pop();
            cout << current->data << " ";
            if (current->left != nullptr)
            {
                q.push(current->left);
            }
            if (current->right != nullptr)
            {
                q.push(current->right);
            }
        }
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

void preorder(node *root)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
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
        cout<<  "6. Delete Node\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        choice = getValidatedInt();

        switch (choice)
        {
        case 1:
            cout << "Enter the node value: ";
            node_value = getValidatedInt();
            root = insertnode(root, node_value);
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

       

        case 6: // Exit
            cout << "Enter the delete node value: ";
            node_value = getValidatedInt();
            root = deleteFromBst(root, node_value);
            cout << "Node deleted successfully.\n";
            break;
        case 7:
            cout<<"Exit,goodbye\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 7);

    return 0;
}