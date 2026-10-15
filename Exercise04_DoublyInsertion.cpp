#include <iostream>
using namespace std;
struct DNode { int data; DNode* prev; DNode* next; };
void insertBack(DNode*& head, DNode*& tail, int value) {
    DNode* node = new DNode{value, tail, nullptr};
    if (tail) tail->next = node; else head = node;
    tail = node;
}
void insertFront(DNode*& head, DNode*& tail, int value) {
    DNode* node = new DNode{value, nullptr, head};
    if (head) head->prev = node; else tail = node;
    head = node;
}
bool insertAfterValue(DNode*& head, DNode*& tail, int target, int value) {
    for (DNode* p = head; p; p = p->next) {
        if (p->data == target) {
            DNode* node = new DNode{value, p, p->next};
            if (p->next) p->next->prev = node; else tail = node;
            p->next = node;
            return true;
        }
    }
    return false;
}
void printForward(DNode* head) {
    for (DNode* p = head; p; p = p->next) cout << p->data << (p->next ? " <-> " : "\n");
    if (!head) cout << "Empty\n";
}
void printBackward(DNode* tail) {
    for (DNode* p = tail; p; p = p->prev) cout << p->data << (p->prev ? " <-> " : "\n");
    if (!tail) cout << "Empty\n";
}
void clear(DNode*& head) {
    while (head) { DNode* p = head; head = head->next; delete p; }
}
int main() {
    DNode* head = nullptr; DNode* tail = nullptr;
    for (int value : {10, 20, 30, 40, 50}) insertBack(head, tail, value);
    insertFront(head, tail, 5);
    insertAfterValue(head, tail, 20, 25);
    insertBack(head, tail, 60);
    printForward(head); printBackward(tail); clear(head);
}
