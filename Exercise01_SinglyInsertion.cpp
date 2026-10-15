#include <iostream>
using namespace std;
struct Node { int data; Node* next; };
Node* createList(int n) {
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 1; i <= n; ++i) {
        Node* node = new Node{i, nullptr};
        if (!head) head = node;
        else tail->next = node;
        tail = node;
    }
    return head;
}
void printList(Node* head) {
    for (Node* p = head; p; p = p->next) cout << p->data << (p->next ? " -> " : "\n");
    if (!head) cout << "Empty\n";
}
void insertFront(Node*& head, int value) {
    head = new Node{value, head};
}
bool insertAfterPosition(Node* head, int position, int value) {
    if (position < 1) return false;
    Node* p = head;
    for (int i = 1; p && i < position; ++i) p = p->next;
    if (!p) return false;
    p->next = new Node{value, p->next};
    return true;
}
void insertBack(Node*& head, int value) {
    Node* node = new Node{value, nullptr};
    if (!head) { head = node; return; }
    Node* p = head;
    while (p->next) p = p->next;
    p->next = node;
}
void clear(Node*& head) {
    while (head) { Node* p = head; head = head->next; delete p; }
}
int main() {
    Node* head = createList(10);
    insertFront(head, 0); printList(head);
    insertAfterPosition(head, 5, 99); printList(head);
    insertBack(head, 11); printList(head);
    clear(head);
}
