// AED 2022/2023 - Aula Pratica 12
// Pedro Ribeiro (DCC/FCUP) [last update: 11/12/2022]

#include "graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

// Depth-First Search: example implementation
void Graph::dfs(int v) {
    // show node order
    // cout << v << " ";
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}

// Breadth-First Search: example implementation
void Graph::bfs(int v) {
    for (int i = 1; i <= n; i++){ nodes[i].visited = false; nodes[i].distance = -1;}
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    nodes[v].distance = 0;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        // show node order
        //cout << u << " ";
        for (auto e: nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance+1;
            }
        }
    }
}

int Graph::maxbfs(int v) {
    int max = 0;
    for (int i = 1; i <= n; i++){ nodes[i].visited = false; nodes[i].distance = -1;}
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    nodes[v].distance = 0;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        // show node order
        //cout << u << " ";
        for (auto e: nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance+1;
                if(nodes[w].distance == -1){
                    return -1;
                }
                else if(nodes[w].distance > max) max = nodes[w].distance;
            }
        }
    }
    return max;
}


// ----------------------------------------------------------
// Exercicio 1a: Distáncia entre dois nós
// ----------------------------------------------------------
// TODO
int Graph::distance(int a, int b) {
    bfs(a);
    return nodes[b].distance;
}

// ----------------------------------------------------------
// Exercicio 1.b: Diâmetro
// ----------------------------------------------------------
// TODO
int Graph::diameter() {
   int max = 0;
   for(int i = 0; i<nodes.size(); i++){
       if(!nodes[i].visited && i>1) return -1;
       int res = maxbfs(i);
       if(res == -1) return -1;
       else if(res> max) max = res;
   }
    return max;
}

