#include <iostream>
#include <string>
using namespace std;
struct Song { string name; Song* prev; Song* next; };
class Playlist {
    Song* head = nullptr;
    Song* tail = nullptr;
    Song* current = nullptr;
public:
    void addSong(const string& name) {
        Song* p = new Song{name, tail, nullptr};
        if (tail) tail->next = p; else head = p;
        tail = p;
        if (!current) current = p;
    }
    bool removeSong(const string& name) {
        for (Song* p = head; p; p = p->next) if (p->name == name) {
            Song* next = p->next ? p->next : p->prev;
            if (p->prev) p->prev->next = p->next; else head = p->next;
            if (p->next) p->next->prev = p->prev; else tail = p->prev;
            if (current == p) current = next;
            delete p; return true;
        }
        return false;
    }
    void nextSong() { if (current && current->next) current = current->next; }
    void previousSong() { if (current && current->prev) current = current->prev; }
    void showCurrentSong() const { cout << (current ? current->name : "No song") << '\n'; }
    void print() const {
        for (Song* p = head; p; p = p->next) cout << p->name << (p == current ? " [playing]" : "") << (p->next ? " <-> " : "\n");
        if (!head) cout << "Empty\n";
    }
    ~Playlist() { while (head) { Song* p = head; head = head->next; delete p; } }
};
int main() {
    Playlist playlist;
    playlist.addSong("Song A"); playlist.addSong("Song B"); playlist.addSong("Song C");
    playlist.showCurrentSong(); playlist.nextSong(); playlist.showCurrentSong();
    playlist.removeSong("Song B"); playlist.showCurrentSong(); playlist.print();
    playlist.removeSong("Song A"); playlist.removeSong("Song C"); playlist.showCurrentSong();
}
