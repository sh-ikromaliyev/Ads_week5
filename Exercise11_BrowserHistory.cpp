#include <iostream>
#include <string>
using namespace std;
struct Page { string name; Page* prev; Page* next; };
class BrowserHistory {
    Page* head = nullptr;
    Page* tail = nullptr;
    Page* current = nullptr;
public:
    void visitPage(const string& name) {
        if (!current) {
            current = head = tail = new Page{name, nullptr, nullptr};
            return;
        }
        Page* p = current->next;
        while (p) { Page* next = p->next; delete p; p = next; }
        current->next = nullptr;
        tail = current;
        Page* node = new Page{name, current, nullptr};
        current->next = node; tail = current = node;
    }
    void goBack() { if (current && current->prev) current = current->prev; }
    void goForward() { if (current && current->next) current = current->next; }
    void showCurrentPage() const { cout << (current ? current->name : "No page") << '\n'; }
    void printHistory() const {
        for (Page* p = head; p; p = p->next) cout << p->name << (p == current ? " [current]" : "") << (p->next ? " -> " : "\n");
        if (!head) cout << "Empty\n";
    }
    ~BrowserHistory() { while (head) { Page* p = head; head = head->next; delete p; } }
};
int main() {
    BrowserHistory browser;
    browser.visitPage("Google"); browser.visitPage("YouTube"); browser.visitPage("GitHub");
    browser.goBack(); browser.goBack(); browser.goForward(); browser.visitPage("ChatGPT");
    browser.showCurrentPage(); browser.printHistory();
}
