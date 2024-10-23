#include <iostream>
#include <climits>
using namespace std;

struct client_node {
    int processing_time;
    client_node *next;
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

class cash_register {
public:
    fifo_queue queue;
    int waiting_time;
    char flag;

    cash_register() {
        waiting_time = 0;
        flag = 'z';
    }

    void set_flag(char flag) {
        this->flag = flag;
    }

    void add_client(int time_to_process) {
        queue.add_last(time_to_process);
        waiting_time += time_to_process;
    }

    int get_size() {
        return queue.get_size();
    }

    void remove_first() {
        queue.remove_first();
    }

    void process_clients(int time) {
        while(time > 0 && !queue.is_empty()) {
            if(queue.get_head()->processing_time <= 0) {
                queue.remove_first();
                if (queue.is_empty()) {
                    break;
                }
            }
            time--;
            queue.get_head()->processing_time--;
            waiting_time--;
        }
    }
};

int find_shortest_line_by_time(cash_register* registers, int num_registers) {
    int shortest_line = -1;
    int shortest_time = INT_MAX;
    for (int i = 0; i < num_registers; i++) {
        if(registers[i].flag == 'o' && registers[i].waiting_time < shortest_time) {
            shortest_time = registers[i].waiting_time;
            shortest_line = i;
        }
    }
    return shortest_line;
}

void show_results(cash_register registers[], int num_registers) {
    for (int j = 0; j < num_registers; j++) {
        if(registers[j].flag == 'z') {
            cout << "K" << j << ": z, ";
        } else if(registers[j].flag == 'o') {
            cout << "K" << j << ": " << registers[j].get_size() << " clients, " << registers[j].waiting_time << "s, ";
        }
    }
}

int main() {
    int simulation_time, num_registers, efficiency, time_to_pay;
    cin >> simulation_time >> num_registers >> efficiency >> time_to_pay;
    cash_register registers[num_registers];
    while(simulation_time > 0) {
        char flag;
        cin >> flag;
        if(flag == 'o') {
            int index;
            cin >> index;
            registers[index].set_flag(flag);
        } else if (flag == 'z') {
            int index;
            cin >> index;
            while(!registers[index].queue.is_empty()) {
                int shortest_line = find_shortest_line_by_time(registers, num_registers);
                registers[shortest_line].add_client(registers[index].queue.get_head()->processing_time);
                registers[index].remove_first();
            }
            registers[index].set_flag(flag);
        } else if (flag == 'k') {
            int time, items;
            cin >> time >> items;
            for(int i = 0; i < num_registers; i++) {
                if(registers[i].flag == 'o') {
                    registers[i].process_clients(time);
                }
            }
            int shortest_line = find_shortest_line_by_time(registers, num_registers);
            registers[shortest_line].add_client(items * efficiency + time_to_pay);
            simulation_time -= time;
        }
    }
    show_results(registers, num_registers);
    return 0;
}
