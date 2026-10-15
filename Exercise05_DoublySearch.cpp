#include <iostream>
using namespace std;
struct DNode { int data; DNode* prev; DNode* next; };
void append(DNode*& head, DNode*& tail, int value) {
    DNode* node = new DNode{value, tail, nullptr};
    if (tail) tail->next = node; else head = node;
    tail = node;
}
DNode* search(DNode* head, int value) {
    for (DNode* p = head; p; p = p->next) if (p->data == value) return p;
    return nullptr;
}
void clear(DNode*& head) {
    while (head) { DNode* p = head; head = head->next; delete p; }
}
int main() {
    DNode* head = nullptr; DNode* tail = nullptr;
    for (int value : {5, 10, 20, 25, 30, 40, 50, 60}) append(head, tail, value);
    for (int value : {25, 100}) cout << value << (search(head, value) ? " found\n" : " not found\n");
    clear(head);
}
