#include <iostream>
using namespace std;
struct Node { int data; Node* next; };
Node* createList(int n) {
    Node* head = nullptr; Node* tail = nullptr;
    for (int i = 1; i <= n; ++i) {
        Node* node = new Node{i, nullptr};
        if (!head) head = node; else tail->next = node;
        tail = node;
    }
    return head;
}
void printList(Node* head) {
    for (Node* p = head; p; p = p->next) cout << p->data << (p->next ? " -> " : "\n");
    if (!head) cout << "Empty\n";
}
bool deleteFront(Node*& head) {
    if (!head) return false;
    Node* p = head; head = head->next; delete p; return true;
}
bool deleteAtPosition(Node*& head, int position) {
    if (position < 1 || !head) return false;
    if (position == 1) return deleteFront(head);
    Node* p = head;
    for (int i = 1; p && i < position - 1; ++i) p = p->next;
    if (!p || !p->next) return false;
    Node* victim = p->next; p->next = victim->next; delete victim; return true;
}
bool deleteBack(Node*& head) {
    if (!head) return false;
    if (!head->next) { delete head; head = nullptr; return true; }
    Node* p = head;
    while (p->next->next) p = p->next;
    delete p->next; p->next = nullptr; return true;
}
void clear(Node*& head) {
    while (head) { Node* p = head; head = head->next; delete p; }
}
int main() {
    Node* head = createList(10);
    deleteFront(head); printList(head);
    deleteAtPosition(head, 5); printList(head);
    deleteBack(head); printList(head);
    clear(head);
}
