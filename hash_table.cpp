#include <iostream>
#include <limits> // For numeric limits
#define TABLE_SIZE 10
using namespace std;

class node {
public:
    int data;
    node* next;
    node(int d) {
        data = d;
        next = NULL;
    }
};

class Hashing {
    node* table[TABLE_SIZE];

public:
    Hashing() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = NULL;
        }
    }

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

    void insert(int key) {
        int index = hashFunction(key);
        node* newNode = new node(key);
        if (table[index] == NULL) {
            table[index] = newNode;
        } else {
            node* temp = table[index];
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "\nIndex: " << i << " : ";
            node* temp = table[i];
            while (temp != NULL) {
                cout << temp->data << " -> ";
                temp = temp->next;
            }
            cout << "NULL";
        }
        cout << endl;
    }
};

int getValidatedInt() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(1000, '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid integer: ";
        } else {
            return value; // Valid input
        }
    }
}

int main() {
    Hashing ht;
    int choice;
    do {
        cout << "Enter 1: For Insert\n";
        cout << "Enter 2: For Display\n";
        cout << "Enter 3: For Exit\n";
        choice = getValidatedInt(); // Get a validated integer input

        switch (choice) {
        case 1: { 
            cout << "\nEnter any number: ";
            int n = getValidatedInt(); // Call the validated input function
            ht.insert(n);
            break;
        }
        case 2: 
            ht.display();
            break;
        case 3: 
            break;
        default:
            cout << "\nInvalid choice! Please select a valid option.\n";
            break;
        }
    } while (choice != 3); 

    return 0;
}
