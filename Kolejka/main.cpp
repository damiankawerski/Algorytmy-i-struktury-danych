#include <iostream>

// p to jest czas w sekundach od początku symulacji albo od ostatniego klienta w kolejce
// r - liczba produktów w koszyku
// a - id kasy
// z - time for client to pay
using namespace std;

struct node {
    int p;              // time in seconds from the beginning of the simulation or from the last client in the queue
    int r;              // number of products in the basket
    node* next;
};

class fifo_List {
public:
    node *head, *tail;
    int id;             // id of the queue
    char f;             // flag of status in the queue in k, o, z
    int time_to_end;    // time to end of the queue

    fifo_List(int id) {
        head = nullptr;
        tail = nullptr;
        this->id = id;
        time_to_end = 0;    // this might be bad idea
    }

    bool is_empty() {
        return head == nullptr;
    }

    void add_last(int r, int p) {
        node *temp = new node();
        temp->r = r;
        temp->p = p;
        temp->next = nullptr;

        if(is_empty()) {
            head = tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    void remove_first() {
        if(is_empty()) {
            return;
        }

        node *temp = head;
        head = head->next;

        if(head == nullptr) {
            tail = nullptr;
        }

        delete temp;
    }

    ~fifo_List() {
        while(!is_empty()) {
            remove_first();
        }
    }
};


int main() {
    unsigned int t;         // time of simulation
    unsigned int i;         // number of queues
    unsigned int s;         // efficienct of queues
    unsigned int z;         // time for client to pay
    cin >> t >> i >> s >> z;

    fifo_List **queues = new fifo_List*[i];

    while(t > 0) {

    }


    delete[] queues;
}
