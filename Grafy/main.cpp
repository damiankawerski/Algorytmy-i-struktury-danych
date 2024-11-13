#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <limits>
#include <algorithm>


using namespace std;

class graph {
private:
    unordered_map<int, vector<int>> adj_list;
    int num_vertices;
public:
    graph(int num_vertices) {
        this->num_vertices = num_vertices;
        adj_list = unordered_map<int, vector<int>>();
        for (int i = 0; i < num_vertices; i++) {
            adj_list[i] = vector<int>();
        }
    }

    ~graph() {
        adj_list.clear();
    }

    void add_edge(int u, int v) {
        adj_list[u].push_back(v);
    }

    int get_end() {
        for(auto i : adj_list) {
            for(auto j : i.second) {
                if(adj_list[j].empty()) {
                    return j;
                }
            }
        }
        return -1;
    }

    vector<int> find_shortest_odd_path(int start) {
       int end = get_end();
       stack<int> s;
       vector<int> result;

       while(!s.empty()) {
             s.push(start);

       }
    }
};

int main() {
    graph g(6);
    g.add_edge(0, 1);
    g.add_edge(1, 5);
    g.add_edge(2, 0);
    g.add_edge(2, 1);
    g.add_edge(3, 2);
    g.add_edge(3, 4);
    g.add_edge(4, 0);

    vector<int> result = g.find_shortest_odd_path(3);
    for(auto i : result) {
        cout << i << " ";
    }
    return 0;
}