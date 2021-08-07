#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> >& adj, int s, int t) {
   
    size_t n = adj.size(); //no of nodes
    vector<int> dist(n, n + 1);
    queue<int> q;
    q.push(s);
    dist[s] = 0;

    while (!q.empty()) {

        for (size_t i = 0; i < adj[q.front()].size(); i++) {
            if (dist[adj[q.front()][i]] == n + 1) { //if the neighbour node hasn't been yet, update it's distance and put it in the queue
                dist[adj[q.front()][i]] = dist[q.front()] + 1;
                q.push(adj[q.front()][i]);
            }
        }
       
        q.pop();
    }

    if (dist[t] == n + 1)
        return -1;
    else
        return dist[t];
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, s, t);
   
    return 0;
}
