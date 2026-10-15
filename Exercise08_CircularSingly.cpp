#include <iostream>
using namespace std;
struct Node { int data; Node* next; };
void append(Node*& head, Node*& tail, int value) {
    Node* node = new Node{value, nullptr};
    if (!head) { head = tail = node; node->next = head; }
    else { tail->next = node; tail = node; tail->next = head; }
}
void printCircular(Node* head) {
    if (!head) { cout << "Empty\n"; return; }
    Node* p = head;
    do {
        cout << p->data;
        p = p->next;
        cout << (p != head ? " -> " : "\n");
    } while (p != head);
}
void clear(Node*& head) {
    if (!head) return;
    Node* p = head->next;
    while (p != head) { Node* next = p->next; delete p; p = next; }
    delete head; head = nullptr;
}
int main() {
    Node* head = nullptr; Node* tail = nullptr;
    for (int value : {10, 20, 30, 40, 50}) append(head, tail, value);
    printCircular(head); clear(head);
}
