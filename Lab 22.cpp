// COMSC-210 | Lab 22 | Expanded Doubly Linked List
#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    /// @brief Deletes the node at the head
    void pop_front(){
        if(!head){
            cout << "Empty list" << endl;
            return;
        }

        Node* remove = head;
        head = head->next;
        head->prev = nullptr; 

        delete remove;
    }

    /// @brief Deletes the node at the tail
    void pop_back(){
        if(!tail){
            cout << "Empty list" << endl;
            return;
        }

        Node* remove = tail;
        tail = tail->prev;
        tail->next = nullptr;

        delete remove;
    }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    /// @brief Deletes the node at the given index
    /// @param index the index where the node will be deleted
    void delete_pos(int index){
        // Valid index check
        if (index < 0){
            cout << "Index must be greater than or equal to 0" << endl;
        }
        // Checks if the list is empty
        if(!head){
            cout << "Empty list" << endl;
            return;
        }

        Node* current = head;

        // Iterates through list and checks to see if the index is out of bounds
        for (int i = 0; i < index; i++){
            current = current->next;

            if(!current){
                cout << "Out of bounds: Index greater than list size" << endl;
                return;
            }
        }

        if(!(current == head)) {current->prev->next = current->next;} // Redirects the previous node to the next node

        // Redirects the head instead of the previous node as there is no previous node
        else{
            head = head->next;
            head->prev = nullptr;
        } 

        if(!(current == tail)) {current->next->prev = current->prev;} // Redirects the next node to the previous node

        // Redirects the tail instead of the next node as there is no next node
        else{
            tail = tail->prev;
            tail->next = nullptr; 
        } 
        

        delete(current);
        current = nullptr;
    }

    void delete_val(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(i);


    cout << "Initial List" << endl;
    cout << "List forward: ";
    list.print();
    cout << endl;

    cout << "Deleting tail node with .delete_pos()" << endl;
    list.delete_pos(size-1);
    cout << "List forward: ";
    list.print();
    cout << endl;

    cout << "Deleting 5th index node with .delete_pos()" << endl;
    list.delete_pos(5);
    cout << "List forward: ";
    list.print();
    cout << endl;

    cout << "Deleting head node with .delete_pos()" << endl;
    list.delete_pos(0);
    cout << "List forward: ";
    list.print();
    cout << endl;



    cout << "Using .pop_back()" << endl;
    list.pop_back();
    cout << "List forward: ";
    list.print();
    cout << endl;

    cout << "Using .pop_front()" << endl;
    list.pop_front();
    cout << "List forward: ";
    list.print();
    cout << endl;

    cout << "Using invalid inputs" << endl;
    cout << "\nUsing a negative index of (-1) for .delete_pos()" << endl;
    list.delete_pos(-1);
    cout << "\nUsing an index thats out of bounds for .delete_pos()" << endl;
    list.delete_pos(size);

    return 0;
}
