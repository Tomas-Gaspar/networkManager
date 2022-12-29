#include <queue>
#include <unordered_set>
#include "Graph.h"

Graph::Graph() {}
Graph::Graph(int num): n(num), nodes(num+1) {}

void Graph::addFlight(int src, int dest, const Airline* airline) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, airline});
}

void Graph::bfs(queue<int> q, unordered_set<string> preferences) {
    for (int i=1; i<=n; i++) {
        nodes[i].visited = false;
        nodes[i].dist = -1;
        nodes[i].path = vector<int>();
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (!nodes[u].path.empty())
            nodes[u].dist = nodes[nodes[u].path.front()].dist + 1;
        else{
            nodes[u].visited = true;
            nodes[u].dist = 0;
        }
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (((nodes[w].path.empty() && !nodes[w].visited)
            || (!nodes[w].path.empty() && nodes[nodes[w].path.front()].dist == nodes[u].dist))
            && (preferences.empty() || preferences.find(e.airline->getCode()) != preferences.end())) {
                if (nodes[w].path.empty())
                    q.push(w);
                nodes[w].visited = true;
                bool repeat = false;
                for (int i : nodes[w].path)
                    if (i == u)
                        repeat = true;
                if (!repeat)
                    nodes[w].path.push_back(u);
            }
        }
    }
}

vector<Graph::Node> Graph::getNodes() {
    return nodes;
}