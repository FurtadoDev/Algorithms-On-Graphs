#include <iostream>
#include <vector>

using std::vector;
using std::pair;


void dfs(vector<vector<int> >& adj, int node, vector<int>& explored) {
    explored[node] = 1;
    for (size_t i = 0; i < adj[node].size(); i++) {
        if (explored[adj[node][i]] == 0) {
            dfs(adj, adj[node][i], explored);
        }
    }
}

int number_of_components(vector<vector<int> >& adj) {
    int res = 0;
   
    size_t n = adj.size();
    vector<int> explored;
    for (int i = 0; i < n; i++) {
        explored.push_back(0);
    }

    for (int i = 0; i < n; i++) {
        if (explored[i] == 0) {
            res += 1;
            dfs(adj, i, explored);
        }
    }

    explored.clear();
   
    return res;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    std::cout << number_of_components(adj);
}
