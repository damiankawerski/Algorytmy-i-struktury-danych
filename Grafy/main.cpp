#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:
    vector<vector<int>> adj;
    int vertices;
public:
    Graph(int n) {
        vertices = n;
        adj.resize(n);
    }

    ~Graph() {
        adj.clear();
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool is_cycle() {
        for(int i = 0 ; i < vertices ; i++) {
            if(adj[i].empty()) {
                return false;
            }
        }
        return true;
    }

    void sort_adj() {
        for(int i = 0 ; i < vertices ; i++) {
            sort(adj[i].begin(), adj[i].end());
        }
    }

    vector<int> bfs(int start) {
        sort_adj();
        vector<bool> visited(vertices, false);
        vector<pair<int, int>> parents(vertices, {-1, -1});
        queue<int> queue;
        queue.push(start);
        visited[start] = true;

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();

            if (adj[current].empty()) {
                vector<int> path;
                path.push_back(current);
                int v = current;
                while (v != start) {
                    path.push_back(parents[v].second);
                    path.push_back(parents[v].first);
                    v = parents[v].first;
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            for(int temp_parent : adj[current]) {
                for(int child : adj[temp_parent]) {
                    if (!visited[child]) {
                        visited[child] = true;
                        queue.push(child);
                        parents[child] = {current, temp_parent};
                    }
                }
            }
        }
        return {};
    }
};

// first - rodzic główny
// second - rodzic pomiedzy

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int tests, vertices, edges, start;
    cin >> tests;

    while(tests--) {
        cin >> vertices >> edges >> start;
        Graph graph(vertices);
        for(int i = 0 ; i < edges ; i++) {
            int u, v;
            cin >> u >> v;
            graph.addEdge(u, v);
        }
        vector<int> path = graph.bfs(start);

        cout << "\n";
        // jeśli ścieżka jest pusta i istnieje cykl
        if(path.empty() && graph.is_cycle()) {
            cout << "PETLA\n";
            continue;
        }
        // jeśli nie ma ścieżki
        if(path.empty()) {
            cout << "NIE\n";
            continue;
        }
        cout << "TAK\n";
        for(int i = 0 ; i < path.size() ; i++) {
            cout << path[i] << " ";
        }
    }
    return 0;
}