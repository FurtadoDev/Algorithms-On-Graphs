#include <iostream>
#include <vector>

using std::vector;
using std::pair;


int dfs(vector<vector<int> >& adj, int src, int dst, vector<int> explored) {
   
    if(src == dst) return 1;

    explored[src] = 1;

    for (size_t i = 0; i < adj[src].size(); i++) {
        if (explored[adj[src][i]] == 0)
            return dfs(adj, adj[src][i], dst, explored);
    }

    return 0;
}


int reach(vector<vector<int> >& adj, int x, int y) {

    vector<int> explored;
    for (size_t i = 0; i < adj.size(); i++) {
        explored.push_back(0);
    }

    int result = dfs(adj, x, y, explored);
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
        adj[y - 1].push_back(x - 1);
    }
    int x, y;
    std::cin >> x >> y;
    std::cout << reach(adj, x - 1, y - 1);
    return 0;
}
