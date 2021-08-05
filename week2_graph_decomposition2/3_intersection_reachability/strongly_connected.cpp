#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void dfs_reverse(vector<vector<int> >& adj_reverse, vector<int>& visited, vector<int>& order, int x) {

    visited[x] = 1;
    for (size_t i = 0; i < adj_reverse[x].size(); i++) {
        if (visited[adj_reverse[x][i]] == 0)
            dfs_reverse(adj_reverse, visited, order, adj_reverse[x][i]);
    }

    order.push_back(x);
}

void dfs_forward(vector<vector<int> >& adj, vector<int>& visited, int x) {

    visited[x] = 1;
    for (size_t i = 0; i < adj[x].size(); i++) {
        if (visited[adj[x][i]] == 0)
            dfs_forward(adj, visited, adj[x][i]);
    }
}

int number_of_strongly_connected_components(vector<vector<int> > adj) {
    int result = 0;
    size_t n = adj.size();
    vector<vector<int> > adj_reverse(n, vector<int>());
    vector<int> visited(n, 0);
    vector<int> order;

    //Step 1 : Reverse the graph
    for (size_t i = 0; i < adj.size(); i++) {
        for (size_t j = 0; j < adj[i].size(); j++) {
            adj_reverse[adj[i][j]].push_back(i);
        }
    }

    //Step 2 : Run DFS on the reverse graph
    for (size_t i = 0; i < adj_reverse.size(); i++) {
        if(visited[i] == 0)
            dfs_reverse(adj_reverse, visited, order, i);
    }
    
    //Step 3 : Clear the visted vector
    for (size_t i = 0; i < visited.size(); i++) {
        visited[i] = 0;
    }

    //Step 4 : Run DFS on the real graph starting with the node that was explored the last
    for (int i = n - 1; i >= 0; i--) {
        if (visited[order[i]] == 0) {
            result += 1;
            dfs_forward(adj, visited, order[i]);
        }
    }


    //Step 5 : Clear memory
    visited.clear();
    order.clear();
    for (size_t i = 0; i < adj_reverse.size(); i++) {
        adj_reverse[i].clear();
    }
    adj_reverse.clear();

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
    std::cout << number_of_strongly_connected_components(adj);
}
