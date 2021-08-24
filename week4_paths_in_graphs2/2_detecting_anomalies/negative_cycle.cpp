#include <iostream>
#include <vector>

using std::vector;

int negative_cycle(vector<vector<int> >& adj, vector<vector<int> >& cost) {

    size_t n = adj.size();
    vector<long long> distance(n, std::numeric_limits<long long>::max());
    distance[0] = 0;

    for (size_t i = 1; i < n; i++) { // edge-budget 1 to n-1
        //Relax
        for (size_t i = 0; i < adj.size(); i++) {
            for (size_t j = 0; j < adj[i].size(); j++) {
                if (distance[i] != std::numeric_limits<long long>::max()) {
                    if (distance[adj[i][j]] > distance[i] + cost[i][j])
                        distance[adj[i][j]] = distance[i] + cost[i][j];
                }
            }
        }
    }


    //Relax : call relax for the nth time here to detect -ve cycles
    for (size_t i = 0; i < adj.size(); i++) {
        for (size_t j = 0; j < adj[i].size(); j++) {
            if (distance[i] != std::numeric_limits<long long>::max()) {
                if (distance[adj[i][j]] > distance[i] + cost[i][j]) {
                    //distance[adj[i][j]] = distance[i] + cost[i][j];
                    distance.clear();
                    return 1; //cycle detected
                }
            }
        }
    }


    return 0;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cout << negative_cycle(adj, cost);
}
