#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
using Clock = chrono::steady_clock;
struct SNode { int data; SNode* next; };
struct DNode { int data; DNode* prev; DNode* next; };
SNode* buildS(int n) {
    SNode* head = nullptr; SNode* tail = nullptr;
    for (int i = 0; i < n; ++i) {
        SNode* p = new SNode{i, nullptr};
        if (!head) head = p; else tail->next = p;
        tail = p;
    }
    return head;
}
DNode* buildD(int n) {
    DNode* head = nullptr; DNode* tail = nullptr;
    for (int i = 0; i < n; ++i) {
        DNode* p = new DNode{i, tail, nullptr};
        if (!head) head = p; else tail->next = p;
        tail = p;
    }
    return head;
}
void clearS(SNode* head) { while (head) { SNode* p = head; head = head->next; delete p; } }
void clearD(DNode* head) { while (head) { DNode* p = head; head = head->next; delete p; } }
template<class F> double averageMicros(F operation, int repetitions = 7) {
    double total = 0;
    for (int i = 0; i < repetitions; ++i) {
        auto start = Clock::now(); operation(); auto end = Clock::now();
        total += chrono::duration<double, micro>(end - start).count();
    }
    return total / repetitions;
}
int main() {
    cout << fixed << setprecision(2);
    cout << "Type,N,InsertFront_us,SearchLast_us,InsertBackNoTail_us\n";
    for (int n : {1000, 10000, 50000}) {
        double sf = averageMicros([&] { SNode* p = new SNode{-1, nullptr}; delete p; });
        double ss = averageMicros([&] { SNode* h = buildS(n); volatile SNode* found = nullptr; for (SNode* p = h; p; p = p->next) if (p->data == n - 1) found = p; (void)found; clearS(h); }, 5);
        double sb = averageMicros([&] { SNode* h = buildS(n); SNode* p = new SNode{n, nullptr}; if (!h) h = p; else { SNode* q = h; while (q->next) q = q->next; q->next = p; } clearS(h); }, 5);
        double df = averageMicros([&] { DNode* p = new DNode{-1, nullptr, nullptr}; delete p; });
        double ds = averageMicros([&] { DNode* h = buildD(n); volatile DNode* found = nullptr; for (DNode* p = h; p; p = p->next) if (p->data == n - 1) found = p; (void)found; clearD(h); }, 5);
        double db = averageMicros([&] { DNode* h = buildD(n); DNode* p = new DNode{n, nullptr, nullptr}; if (!h) h = p; else { DNode* q = h; while (q->next) q = q->next; p->prev = q; q->next = p; } clearD(h); }, 5);
        cout << "Singly," << n << "," << sf << "," << ss << "," << sb << '\n';
        cout << "Doubly," << n << "," << df << "," << ds << "," << db << '\n';
    }
    cout << "Expected Big-O: front insertion O(1), search O(n), end insertion without tail O(n).\n";
}
