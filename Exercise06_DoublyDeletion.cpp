#include <iostream>
using namespace std;
struct DNode { int data; DNode* prev; DNode* next; };
void append(DNode*& head, DNode*& tail, int value) {
    DNode* node = new DNode{value, tail, nullptr};
    if (tail) tail->next = node; else head = node;
    tail = node;
}
void printForward(DNode* head) {
    for (DNode* p = head; p; p = p->next) cout << p->data << (p->next ? " <-> " : "\n");
    if (!head) cout << "Empty\n";
}
void printBackward(DNode* tail) {
    for (DNode* p = tail; p; p = p->prev) cout << p->data << (p->prev ? " <-> " : "\n");
    if (!tail) cout << "Empty\n";
}
bool deleteFront(DNode*& head, DNode*& tail) {
    if (!head) return false;
    DNode* p = head; head = head->next;
    if (head) head->prev = nullptr; else tail = nullptr;
    delete p; return true;
}
bool deleteValue(DNode*& head, DNode*& tail, int value) {
    for (DNode* p = head; p; p = p->next) if (p->data == value) {
        if (p->prev) p->prev->next = p->next; else head = p->next;
        if (p->next) p->next->prev = p->prev; else tail = p->prev;
        delete p; return true;
    }
    return false;
}
bool deleteBack(DNode*& head, DNode*& tail) {
    if (!tail) return false;
    DNode* p = tail; tail = tail->prev;
    if (tail) tail->next = nullptr; else head = nullptr;
    delete p; return true;
}
void clear(DNode*& head) {
    while (head) { DNode* p = head; head = head->next; delete p; }
}
int main() {
    DNode* head = nullptr; DNode* tail = nullptr;
    for (int value : {5, 10, 20, 25, 30, 40, 50, 60}) append(head, tail, value);
    deleteFront(head, tail); printForward(head); printBackward(tail);
    deleteValue(head, tail, 30); printForward(head); printBackward(tail);
    deleteBack(head, tail); printForward(head); printBackward(tail);
    clear(head);
}
