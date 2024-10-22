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
    int processing_time;
    client_node *next;
};

class queue {
private:
    client_node* head;
    client_node* tail;
    int size;
public:
    queue() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    bool is_empty() const {
        return size == 0;
    }

    void add_last(int time_to_process) {
        client_node* new_client = new client_node;
        new_client->processing_time = time_to_process;
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

    client_node* get_head() {
        return head;
    }

    int get_size() const {
        return size;
    }
};