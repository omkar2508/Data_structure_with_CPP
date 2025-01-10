#include <iostream>
#include <limits>
#include <stack>

using namespace std;

class Node {
private:
    int value;
    Node* left;
    Node* centre;
    Node* right;

public:
    Node(int n) {
        value = n;
        left = nullptr;
        centre = nullptr;
        right = nullptr;
    }

    int getValue()  {
        return value;
    }

    Node* getLeft()  {
        return left;
    }

    void setLeft(Node* l) {
        left = l;
    }

    Node* getCentre() {
        return centre;
    }

    void setCentre(Node* c) {
        centre = c;
    }

    Node* getRight()  {
        return right;
    }

    void setRight(Node* r) {
        right = r;
    }

    void setValue(int n) {
        value = n;
    }
};

class Tree {
public:
    Node* addNode(Node* root, int value) {
        if (root == nullptr) {
            root = new Node(value);
            return root;
        }

        if (root==nullptr) {
            root->setLeft(addNode(root->getLeft(), value));
        }
        else if (root->getCentre()==nullptr) {
            root->setCentre(addNode(root->getCentre(), value));  
        }
        else {
            root->setRight(addNode(root->getRight(), value));
        }

        return root;
    }

    Node* deleteNode(Node* root, int value) {
        Node* curr = root;
        Node* prev = nullptr;
        
        
        while (curr != nullptr && curr->getValue() != value) {
            prev = curr;
            if (value < curr->getValue()) {
                curr = curr->getLeft();
            } else if (value > curr->getValue()) {
                curr = curr->getRight();
            }
        }

        if (curr == nullptr) {
            cout << "Element not present" << endl;
            return root;
        }

       
        if (curr->getLeft() == nullptr || curr->getRight() == nullptr) {
            Node* newCurr = (curr->getLeft() != nullptr) ? curr->getLeft() : curr->getRight();

            if (prev == nullptr) {  
                delete curr;
                cout << value << " deleted successfully" << endl;
                return newCurr;
            }

            if (curr == prev->getLeft()) {
                prev->setLeft(newCurr);
            } else {
                prev->setRight(newCurr);
            }
            delete curr;
            cout << value << " deleted successfully" << endl;
        }
       
        else {
            Node* temp = curr->getRight();
            Node* p = nullptr;

            while (temp->getLeft() != nullptr) {
                p = temp;
                temp = temp->getLeft();
            }

            if (p != nullptr) {
                p->setLeft(temp->getRight());
            } else {
                curr->setRight(temp->getRight());
            }

            curr->setValue(temp->getValue());
            delete temp;
            cout << value << " deleted successfully" << endl;
        }

        return root;
    }

    void postorder(Node* root) {
        if (root == nullptr) {
            return;
        }
        postorder(root->getLeft());
        postorder(root->getCentre());
        postorder(root->getRight());
        cout << root->getValue() << " ";
    }

    void preorder(Node* root) {
        if (root == nullptr) {
            return;
        }
        cout << root->getValue() << " ";
        preorder(root->getLeft());
        preorder(root->getCentre());
        preorder(root->getRight());
    }

    void inorder(Node* root) {
        if (root == nullptr) {
            return;
        }

        inorder(root->getLeft());
        cout << root->getValue() << " ";
        inorder(root->getCentre());
        inorder(root->getRight());
    }

};


int getValidInput() {
    int input;
    while (true) {
        cout << " ";
        cin >> input;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(10, '\n');  
            cout << "Invalid input. Please enter a valid integer." << endl;
        } else {
            cin.ignore(10, '\n'); 
            return input;  
        }
    }
}

int main() {
    Tree tree;
    Node* root = nullptr;
    int choice, value, newValue;

    
        cout << "\n1. Add Node\n";
        cout << "2. Delete Node\n";
        cout << "3. Inorder Traversal\n";
        cout << "4. Preorder Traversal\n";
        cout << "5. Postorder Traversal\n";
        cout << "6. Exit\n";
        while (true) {
        cout << "Enter your choice: ";
        choice = getValidInput();

        switch (choice) {
            case 1:
                cout << "Enter value to add: ";
                value = getValidInput();
                root = tree.addNode(root, value);
                cout << value << " added to the tree." << endl;
                break;

            case 2:
                cout << "Enter value to delete: ";
                value = getValidInput();
                root = tree.deleteNode(root, value);
                break;

           
            case 3:
                cout << "Inorder Traversal: ";
                tree.inorder(root);
                cout << endl;
                break;

            case 4:
                cout << "Preorder Traversal: ";
                tree.preorder(root);
                cout << endl;
                break;

            case 5:
                cout << "Postorder Traversal: ";
                tree.postorder(root);
                cout << endl;
                break;

            case 6:
                cout << "Exiting..." << endl;
                return 0;

            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }
}