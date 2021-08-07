#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> >& adj) {
   
    size_t n = adj.size();
    vector<int> dist(n, n + 1);
    queue<int> q;
    dist[0] = 0;
    q.push(0);

    while (!q.empty()) {
        //put all of its neighbours in a queue
        for (size_t j = 0; j < adj[q.front()].size(); j++) {
            //if the node is not yet processed
            if (dist[adj[q.front()][j]] == n + 1) {

                dist[adj[q.front()][j]] = dist[q.front()] + 1;
                q.push(adj[q.front()][j]);

            }
            else { //if the node has already been processed

                if ((dist[adj[q.front()][j]] - dist[q.front()]) % 2 == 0) {
                    while (!q.empty()) {
                        q.pop();
                    }

                    return 0;
                }

            }

        }

        q.pop();
    }

    return 1;
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
    std::cout << bipartite(adj);
   
    return 0;
}
