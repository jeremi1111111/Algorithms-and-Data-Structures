#include <iostream>

struct nodeLN {
    int dest;
    int weight;
    nodeLN* next;
};

void add(nodeLN**& graph, int from, int dest, int weight) {
    nodeLN* p = new nodeLN;
    p->dest = dest;
    p->weight = weight;
    p->next = graph[from];
    graph[from] = p;
    // below only if graph is not directed
    p = new nodeLN;
    p->dest = from;
    p->weight = weight;
    p->next = graph[dest];
    graph[dest] = p;
}

int minDist(int distances[], bool picked[], int nodes) {
    int minVal = INT_MAX, minNode;
    for (int i = 0; i < nodes; i++) {
        if (distances[i] < minVal && picked[i] == false) {
            minNode = i;
            minVal = distances[i];
        }
    }
    return minNode;
}

void dijkstra(nodeLN**& graph, int nodes, int start) {
    bool* picked = new bool[nodes]{};
    int* distances = new int[nodes]{};
    for (int i = 0; i < nodes; i++) {
        distances[i] = INT_MAX;
    }
    distances[start] = 0;
    for (int i = 0; i < nodes - 1; i++) {
        int u = minDist(distances, picked, nodes);
        picked[u] = true;
        nodeLN* p = graph[u];
        while (p) {
            if (picked[p->dest] == false && distances[u] + p->weight < distances[p->dest]) {
                distances[p->dest] = distances[u] + p->weight;
            }
            p = p->next;
        }
    }
    for (int i = 0; i < nodes; i++) {
        std::cout << distances[i] << ' ';
    }
    std::cout << std::endl;
}

void show_LN(nodeLN **graph, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << "LN" << i <<"->";
        nodeLN *printed = graph[i];
        while(printed) {
            std::cout << '[' << printed->dest << ", " << printed->weight << ']' << "->";
            printed = printed->next;
        }
        std::cout << "NULL" << std::endl;
    }
}

int main() {
    nodeLN** graph = nullptr;
    std::cout << "nodes: ";
    int nodes;
    std::cin >> nodes;
    graph = new nodeLN*[nodes];
    for (int i = 0; i < nodes; i++) {
        graph[i] = nullptr;
    }
    std::cout << "edges: ";
    int edges;
    std::cin >> edges;
    std::cout << "graph:\n";
    for (int i = 0; i < edges; i++) {
        int from, dest, weight;
        std::cin >> weight;
        std::cin >> from;
        std::cin >> dest;
        add(graph, from, dest, weight);
    }
    show_LN(graph, nodes);
    dijkstra(graph, nodes, 0);
}