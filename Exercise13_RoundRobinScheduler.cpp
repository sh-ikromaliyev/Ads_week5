#include <iostream>
#include <string>
using namespace std;
struct Task { string name; Task* next; };
class Scheduler {
    Task* tail = nullptr;
    Task* current = nullptr;
public:
    void addTask(const string& name) {
        Task* p = new Task{name, nullptr};
        if (!tail) { tail = current = p; p->next = p; }
        else { p->next = tail->next; tail->next = p; tail = p; }
    }
    bool removeTask(const string& name) {
        if (!tail) return false;
        Task* prev = tail;
        Task* p = tail->next;
        do {
            if (p->name == name) {
                if (p == prev) { delete p; tail = current = nullptr; return true; }
                prev->next = p->next;
                if (p == tail) tail = prev;
                if (p == current) current = p->next;
                delete p; return true;
            }
            prev = p; p = p->next;
        } while (p != tail->next);
        return false;
    }
    void runNextTask() {
        if (!current) { cout << "No tasks\n"; return; }
        cout << current->name << '\n';
        current = current->next;
    }
    ~Scheduler() {
        if (!tail) return;
        Task* head = tail->next; tail->next = nullptr;
        while (head) { Task* p = head; head = head->next; delete p; }
    }
};
int main() {
    Scheduler scheduler;
    scheduler.addTask("A"); scheduler.addTask("B"); scheduler.addTask("C");
    for (int i = 0; i < 7; ++i) scheduler.runNextTask();
    scheduler.removeTask("B");
    for (int i = 0; i < 6; ++i) scheduler.runNextTask();
    scheduler.removeTask("A"); scheduler.removeTask("C"); scheduler.runNextTask();
}
