#include <iostream>
#include <string>
using namespace std;
struct Ticket { int number; string customer; Ticket* next; };
class TicketQueue {
    Ticket* head = nullptr;
    Ticket* tail = nullptr;
public:
    void addTicket(int number, const string& name) {
        Ticket* p = new Ticket{number, name, nullptr};
        if (tail) tail->next = p; else head = p;
        tail = p;
    }
    bool serveNext() {
        if (!head) { cout << "No tickets waiting\n"; return false; }
        Ticket* p = head;
        cout << "Serving " << p->number << ": " << p->customer << '\n';
        head = head->next;
        if (!head) tail = nullptr;
        delete p; return true;
    }
    Ticket* findTicket(int number) const {
        for (Ticket* p = head; p; p = p->next) if (p->number == number) return p;
        return nullptr;
    }
    void printQueue() const {
        for (Ticket* p = head; p; p = p->next) cout << p->number << ": " << p->customer << (p->next ? " -> " : "\n");
        if (!head) cout << "Empty\n";
    }
    ~TicketQueue() {
        while (head) { Ticket* p = head; head = head->next; delete p; }
        tail = nullptr;
    }
};
int main() {
    TicketQueue queue;
    queue.addTicket(101, "Ali"); queue.addTicket(102, "Madina"); queue.addTicket(103, "Jasur");
    queue.printQueue();
    cout << (queue.findTicket(102) ? "Ticket 102 found\n" : "Ticket 102 not found\n");
    queue.serveNext();
    queue.addTicket(104, "Dilnoza");
    queue.printQueue();
}
