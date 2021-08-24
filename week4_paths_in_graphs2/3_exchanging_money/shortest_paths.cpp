#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

void shortest_paths(vector<vector<int> >& adj, vector<vector<int> >& cost, int s, vector<long long>& distance, vector<bool>& reachable, vector<bool>& shortest) {

    size_t n = adj.size();
    distance[s] = 0;

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
                    distance[adj[i][j]] = distance[i] + cost[i][j];
                    shortest[adj[i][j]] = false;
                }
            }
        }
    }
    
    
    //if -ve cycle detected run more rounds to help that -ve infinty to propagate through the graph(run from i=2 to n-1))
    for (size_t i = 2; i < n; i++) { // edge-budget 1 to n-1
        // Relax
        for (size_t i = 0; i < adj.size(); i++) {
            for (size_t j = 0; j < adj[i].size(); j++) {
                if (distance[i] != std::numeric_limits<long long>::max()) {
                    if (distance[adj[i][j]] > distance[i] + cost[i][j]) {
                        distance[adj[i][j]] = distance[i] + cost[i][j];
                        shortest[adj[i][j]] = false;
                    }
                }
            }
        }

    }

    /*
    std::cout << "------------------------" << std::endl;
    for (size_t i = 0; i < distance.size(); i++) {
        std::cout << distance[i] << std::endl;
    }
    std::cout << "------------------------" << std::endl;
    */
    
    
    for (size_t i = 0; i < distance.size(); i++) {
        if (distance[i] != std::numeric_limits<long long>::max()) {
            reachable[i] = true;
        }
    }

}

int main() {

    int n, m, s;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cin >> s;
    s--;
    vector<long long> distance(n, std::numeric_limits<long long>::max());
    vector<bool> reachable(n, false);
    vector<bool> shortest(n, true);
    shortest_paths(adj, cost, s, distance, reachable, shortest);
    for (int i = 0; i < n; i++) {
        if (!reachable[i]) {
            std::cout << "*\n";
        }
        else if (!shortest[i]) {
            std::cout << "-\n";
        }
        else {
            std::cout << distance[i] << "\n";
        }
    }

}
