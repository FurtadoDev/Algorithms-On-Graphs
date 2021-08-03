#include <iostream>
#include <vector>

using std::vector;
using std::pair;

int dfs(vector<vector<int> >& adj, int node, vector<int>& explored) {

    explored[node] = 1;
    //iterate through all of the nodes neighbours
    for (size_t i = 0; i < adj[node].size(); i++) {
        if (explored[adj[node][i]] == 1)
            return 1;
        else
            return dfs(adj, adj[node][i], explored);
    }
    return 0;
}

int acyclic(vector<vector<int> >& adj) {
    //write your code here
    size_t n = adj.size(); //todo :: consider orphan(lone) nodes
    vector<int> explored;
    for (size_t i = 0; i < n; i++) {
        explored.push_back(0);
    }
   
    int result = dfs(adj, 0, explored);
    explored.clear();
    return result;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    std::cout << acyclic(adj);
}
