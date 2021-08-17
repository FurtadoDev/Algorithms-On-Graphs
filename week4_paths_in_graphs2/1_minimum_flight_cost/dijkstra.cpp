#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

long long distance(vector<vector<int> >& adj, vector<vector<int> >& cost, int s, int t) {
    
    int answer;

    //priority queue to store the (V-X) nodes in order of priority
    auto cmp = [](pair<int, int> left, pair<int, int> right) { return (left.second) > (right.second); };
    std::priority_queue<pair<int, int>, std::vector<pair<int, int>>, decltype(cmp)> p_queue(cmp);

    size_t num_nodes = adj.size();
    vector<size_t> processed_nodes(num_nodes, 0);
    vector<int> distances(num_nodes, INT_MAX);

    // intialize the priority queue with the starting vertex
    p_queue.push(std::make_pair(s, 0));
    pair<int, int> temp_pair;

    while (!p_queue.empty()) {
        
        temp_pair = p_queue.top();
        
        //if the node is already processed, ignore it
        if (processed_nodes[temp_pair.first] == 1) {
            
            p_queue.pop();

        }
        else {
            // Core Logic : Whenever, you bring one node to X(by processing it), add it's unprocessed neighbours to the priority queue
            processed_nodes[temp_pair.first] = 1;
            distances[temp_pair.first] = temp_pair.second;

            // add it's neighbours to the priority queue
            for (size_t i = 0; i < adj[temp_pair.first].size(); i++) {
                if (processed_nodes[adj[temp_pair.first][i]] == 0) {
                    p_queue.push(std::make_pair(adj[temp_pair.first][i], temp_pair.second + cost[temp_pair.first][i]));
                }
            }
            
            
            p_queue.pop();
        }
        
    }



    if (distances[t] == INT_MAX) {

        answer = -1;

    }
    else {

        answer = distances[t];

    }

    /*
    for (size_t i = 0; i < distances.size(); i++) {
        std::cout << distances[i] << std::endl;
    }
    */

    processed_nodes.clear();
    distances.clear();

    
    return answer;
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
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, cost, s, t);
    
    // TEST 1 :
    /*
    int n = 5;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    
    adj[0].push_back(1);
    cost[0].push_back(4);
    
    adj[0].push_back(2);
    cost[0].push_back(1);

    adj[1].push_back(3);
    cost[1].push_back(1);

    adj[2].push_back(1);
    cost[2].push_back(2);

    adj[2].push_back(3);
    cost[2].push_back(5);

    adj[3].push_back(4);
    cost[3].push_back(3);

    int s = 0, t = 4;
    distance(adj, cost, s, t);

    */


    // TEST 2:
    /*
    int n = 4;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    adj[0].push_back(1);
    cost[0].push_back(1);

    adj[0].push_back(2);
    cost[0].push_back(4);

    adj[1].push_back(3);
    cost[1].push_back(6);

    adj[1].push_back(2);
    cost[1].push_back(2);

    adj[2].push_back(3);
    cost[2].push_back(3);

    int s = 0, t = 3;
    distance(adj, cost, s, t);

    */

    return 0;
}
