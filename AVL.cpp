#include <iostream>
using namespace std;

class node
{
public:
   int value;
   int height;
   node *left;
   node *right;

   node() : value(0), height(0), left(nullptr), right(nullptr) {}
};
class Stack
{
private:
    struct Node
    {
        node *data; // representing a binary tree node
        Node *next; // used for the stack or queue
    };
    

public:
    Node *topNode;
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
        if (!empty())
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

    bool empty()
    {
        return topNode == nullptr;
    }
};

node *root = nullptr;
Stack s; 
//stack<node*>s;
int height(node *node)
{
   if (node == nullptr)
      return 0;
   return node->height;
}

node *rotateLL(node *current, node *parent)
{
   parent->left = current->right;
   current->right = parent;
   parent->height = 1 + max(height(parent->left), height(parent->right));
   current->height = 1 + max(height(current->left), height(current->right));
   return current;
}

node *rotateRR(node *current, node *parent)
{
   parent->right = current->left;
   current->left = parent;
   parent->height = 1 + max(height(parent->left), height(parent->right));
   current->height = 1 + max(height(current->left), height(current->right));
   return current;
}

node *rotateRL(node *current, node *parent)
{
   node *child = current->left;
   current->left = child->right;
   child->right = current;
   parent->right = child->left;
   child->left = parent;
   current->height = 1 + max(height(current->left), height(current->right));
   parent->height = 1 + max(height(parent->left), height(parent->right));
   child->height = 1 + max(height(child->left), height(child->right));
   return child;
}

node *rotateLR(node *current, node *parent)
{
   node *child = current->right;
   current->right = child->left;
   child->left = current;
   parent->left = child->right;
   child->right = parent;
   current->height = 1 + max(height(current->left), height(current->right));
   parent->height = 1 + max(height(parent->left), height(parent->right));
   child->height = 1 + max(height(child->left), height(child->right));
   return child;
}

void reCalculateHeight(int value)
{
   while (!s.empty())
   {
      node *current = s.top();
      s.pop();
      current->height = 1 + max(height(current->left), height(current->right));
      int bf = height(current->left) - height(current->right);

      node *parent = nullptr;
      if (!s.empty())
         parent = s.top();

      node *balancednode = nullptr;
      if (bf > 1 && current->left->value > value)
      {
         balancednode = rotateLL(current->left, current);
      }
      else if (bf < -1 && current->right->value < value)
      {
         balancednode = rotateRR(current->right, current);
      }
      else if (bf > 1 && current->left->value < value)
      {
         balancednode = rotateLR(current->left, current);
      }
      else if (bf < -1 && current->right->value > value)
      {
         balancednode = rotateRL(current->right, current);
      }

      //node  have parent or not
      if (balancednode)
      {
         if (!parent)
            root = balancednode;
         else
         {
            if (parent->left == current)
               parent->left = balancednode;
            else
               parent->right = balancednode;
         }
      }
   }
}

node* addnode(int value)
{
   node *temp = new node();
   temp->value = value;
   if (root == nullptr)
   {
      root = temp;
      return root;
   }
   node *start = root;
   while (start->value != value)
   {
      s.push(start); 
      if (value < start->value)
      {
         if (start->left == nullptr)
         {
            start->left = temp;
         }
         start = start->left;
      }
      else
      {
         if (start->right == nullptr)
         {
            start->right = temp;
         }
         start = start->right;
      }
   }
   s.push(start);           
   reCalculateHeight(value);
   
   return root; 
}


void preOrderTraversal(node *root)
{
   if (root == nullptr)
      return;

   cout << root->value << " ";
   preOrderTraversal(root->left);
   preOrderTraversal(root->right);
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
        cout << "2. Pre-order Traversal\n";
       
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        choice = getValidatedInt();

        switch (choice)
        {
        case 1:
            cout << "Enter the node value: ";
            node_value = getValidatedInt();
            root = addnode(node_value);
            cout << "Node inserted successfully.\n";
            break;

        case 2:
            if (root == nullptr)
            {
                cout << "The tree is empty. Please insert nodes first.\n";
            }
            else
            {
                cout << "Pre-order Traversal: ";
                preOrderTraversal(root);
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

// int main(){
//    addnode(55);
//     addnode(26);
//      addnode(66);
//       addnode(77);
//       addnode(67);
//       addnode(888);
//       addnode(99);
//       addnode(90);
//       addnode(29);
//       addnode(56);
//       addnode(58);
//       addnode(22);
//       addnode(1);
//       addnode(24);

//       addnode(61);
//       addnode(71);
//       addnode(88);

//       addnode(95);

//       preOrderTraversal(root);


// }