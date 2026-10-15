#include <iostream>
using namespace std;
class DoublyLinkedList {
private:
    struct Node { int data; Node* prev; Node* next; };
    Node* head = nullptr;
    Node* tail = nullptr;
public:
    void insertFront(int value) {
        Node* p = new Node{value, nullptr, head};
        if (head) head->prev = p; else tail = p;
        head = p;
    }
    void insertBack(int value) {
        Node* p = new Node{value, tail, nullptr};
        if (tail) tail->next = p; else head = p;
        tail = p;
    }
    bool search(int value) const {
        for (Node* p = head; p; p = p->next) if (p->data == value) return true;
        return false;
    }
    bool deleteValue(int value) {
        for (Node* p = head; p; p = p->next) if (p->data == value) {
            if (p->prev) p->prev->next = p->next; else head = p->next;
            if (p->next) p->next->prev = p->prev; else tail = p->prev;
            delete p; return true;
        }
        return false;
    }
    void printForward() const {
        for (Node* p = head; p; p = p->next) cout << p->data << (p->next ? " <-> " : "\n");
        if (!head) cout << "Empty\n";
    }
    void printBackward() const {
        for (Node* p = tail; p; p = p->prev) cout << p->data << (p->prev ? " <-> " : "\n");
        if (!tail) cout << "Empty\n";
    }
    ~DoublyLinkedList() {
        while (head) { Node* p = head; head = head->next; delete p; }
        tail = nullptr;
    }
};
int main() {
    DoublyLinkedList list;
    list.insertFront(20); list.insertFront(10); list.insertBack(30); list.insertBack(40);
    list.printForward(); list.printBackward();
    cout << (list.search(30) ? "30 found\n" : "30 not found\n");
    list.deleteValue(30); list.printForward(); list.printBackward();
}
