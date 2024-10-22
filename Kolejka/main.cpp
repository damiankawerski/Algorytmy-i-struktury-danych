#include <climits>
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
    int  r;
    int time_to_process;
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

    void add_last(int r, int time_to_process) {
        client_node* new_client = new client_node;
        new_client->r = r;
        new_client->time_to_process = time_to_process;
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


class cash_register {
public:
    fifo_queue queue;
    int efficiency, time_to_pay, time_of_simulation;
    char f;

    cash_register(int s, int z) {
        efficiency = s;
        time_to_pay = z;
        this->f = 'z';
    }

    ~cash_register() {
        while (!queue.is_empty()) {
            queue.remove_first();
        }
    }

    void open_register() {
        f = 'o';
    }

    void close_register() {
        f = 'z';
        while(!queue.is_empty()) {
            queue.remove_first();
        }
    }

    void add_client(int r) {
        int waiting_time = r * efficiency + time_to_pay;
        queue.add_last(r, waiting_time);
    }

    void process_queue(int p) {
        client_node* client = queue.get_head();
        if (client == nullptr) {
            return;
        }

        while (p > 0 && client != nullptr) {
            if (client->time_to_process <= p) {
                p -= client->time_to_process;
                queue.remove_first();
                client = queue.get_head();
            } else {
                client->time_to_process -= p;
                p = 0;
            }
        }
    }

    int get_number_of_people() {
        return queue.get_size();
    }

    int get_waiting_time() {
        client_node* temp = queue.get_head();
        int waiting_time = 0;
        while(temp != nullptr) {
            waiting_time += temp->time_to_process;
            temp = temp->next;
        }
    }
};

int find_queue_with_lowest_time(cash_register** registers, int i) {
    int min_time = INT_MAX;
    int min_index = -1;
    for (int j = 0; j < i; j++) {
        if(registers[j]->f == 'o') {
            if (registers[j]->get_waiting_time() < min_time) {
                min_time = registers[j]->get_waiting_time();
                min_index = j;
            }
        }
    }
    return min_index;
}

void initialize_registers(cash_register **registers, int i, int s, int z) {
    for (int j = 0; j < i; j++) {
        registers[j] = new cash_register(s, z);
    }
}

void delete_registers(cash_register **registers, int i) {
    for (int j = 0; j < i; j++) {
        delete registers[j];
    }
    delete[] registers;
}

void show_results(cash_register **registers, int i) {
    for (int j = 0; j < i; j++) {
        if(registers[j]->f == 'z') {
            cout << "K" << j << ": z, ";
        } else if(registers[j]->f == 'o') {
            cout << "K" << j << ": " << registers[j]->get_number_of_people() << "o " << registers[j]->get_waiting_time() << "s, ";
        }
    }
}

int main() {
    int t; // czas trwania symulacji
    int i; // liczba kolejek
    int s; // sprawność, ile czasu na jeden produkt
    int z; // czas płatności

    cin >> t >> i >> s >> z;

    cash_register** registers = new cash_register*[i];
    initialize_registers(registers, i, s, z);

    while(t > 0) {
        char f; // flaga kolejki
        int a;   // indeks kolejki
        int p; // czas od rozpoczęcia symulacji albo od ostatniego klienta
        cin >> f;
        if(f == 'o') {
            cin >> a;
            registers[a]->open_register();
        }
        if(f == 'z') {
            cin >> a;
            registers[a]->close_register();
        }
        if(f == 'k') {
            int r;
            cin >> p >> r;
            int index = find_queue_with_lowest_time(registers, i);
            registers[index]->add_client(r);
            for(int j = 0; j < i; j++) {
                registers[j]->process_queue(p);
            }
            t-=p;
        }
    }
    show_results(registers, i);
    delete_registers(registers, i);
}