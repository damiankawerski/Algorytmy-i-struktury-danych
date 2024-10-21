#include <iostream>

using namespace std;

// t - czas trwania symulacji
// i - liczba kolejek
// s - sprawność, ile czasu na jeden produkt
// z - czas płatności
// p - czas od rozpoczęcia symulacji albo od ostatniego klienta
// r - liczba produktów
// a - numer kasy
// f - flaga

struct client_node {
    int p, r;
    client_node* next;
};

class fifo_queue {
private:
    client_node *head;
    client_node *tail;
    int size;
public:
    fifo_queue() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    bool is_empty() {
        return head == nullptr;
    }

    void add_last(int r, int p) {
        client_node* new_client = new client_node;
        new_client->r = r;
        new_client->p = p;
        new_client->next = nullptr;

        if (is_empty()) {
            head = new_client;
            tail = new_client;
        } else {
            tail->next = new_client;
            tail = new_client;
        }
        size++;
    }

    void remove_first() {
        if (is_empty()) {
            return;
        }

        client_node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    int get_size() {
        return size;
    }

    client_node* get_head() {
        return head;
    }
};