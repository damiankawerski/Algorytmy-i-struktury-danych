#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

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
        int counter = 0;
        int result = -1;
        for(auto i : adj_list) {
            for(int j : i.second) {
                if(adj_list[j].empty()) {
                    counter++;
                    result = j;
                    if(counter > 1) {
                        return -1;
                    }
                }
            }
        }
        return result;
    }

    void dfs(int u, int end, vector<bool>& visited, vector<int>& path, vector<vector<int>>& all_paths) {
        visited[u] = true;
        path.push_back(u);

        if (u == end) {
            if(path.size() % 2 != 0) {
                all_paths.push_back(path);
            }
        } else {
            for (int v : adj_list[u]) {
                if (!visited[v]) {
                    dfs(v, end, visited, path, all_paths);
                }
            }
        }

        path.pop_back();
        visited[u] = false;
    }

    vector<int> bfs(int start, int end) {
        queue<pair<int, vector<int>>> q;
        q.push({start, {start}});
        unordered_map<int, bool> visited;

        while (!q.empty()) {
            int u = q.front().first;
            vector<int> path = q.front().second;
            q.pop();

            if (u == end && path.size() % 2 != 0) {
                return path;
            } else {
                for (int v : adj_list[u]) {
                    if (find(path.begin(), path.end(), v) == path.end()) {
                        vector<int> new_path = path;
                        new_path.push_back(v);
                        q.push({v, new_path});
                    }
                }
            }
        }
        return vector<int>();
    }

    vector<vector<int>> find_all_paths_dfs(int start, int end) {
        vector<vector<int>> all_paths;
        vector<int> path;
        vector<bool> visited(num_vertices, false);

        dfs(start, end, visited, path, all_paths);

        sort(all_paths.begin(), all_paths.end());

        return all_paths;
    }

    vector<int> find_path_bfs(int start, int end) {
        vector<int> path = bfs(start, end);
        return path;
    }

    vector<int> find_shortest_odd_path_dfs(int start, int end) {
       vector<vector<int>> all_paths = find_all_paths_dfs(start, end);
        if(all_paths.empty()) {
            return vector<int>();
        } else {
            return all_paths[0];
        }
    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int tests, vertices, edges, start;
    cin >> tests;
    while(tests--) {
        cin >> vertices >> edges >> start;
        graph g(vertices);
        for(int i = 0; i < edges; i++) {
            int u, v;
            cin >> u >> v;
            g.add_edge(u, v);
        }
        int end = g.get_end();
        if(end == -1) {
            cout << "PETLA" << '\n';
        } else {
            //vector<int> result = g.find_shortest_odd_path_dfs(start, end);
            vector<int> result = g.find_path_bfs(start, end);
            if(result.empty()) {
                cout << "NIE" << '\n';
            } else {
                cout << "TAK" << '\n';
                for(int i = 0; i < result.size(); i++) {
                    cout << result[i] << " ";
                }
                cout << '\n';
            }
        }
    }
    return 0;
}

