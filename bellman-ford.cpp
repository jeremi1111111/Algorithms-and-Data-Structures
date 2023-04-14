#include <iostream>

struct nodeLE {
    int from;
    int dest;
    int weight;
    nodeLE* next;
};

void add(nodeLE*& graph, int from, int dest, int weight) {
    nodeLE *p = new nodeLE;
    p->from = from;
    p->dest = dest;
    p->weight = weight;
    p->next = graph;
    graph = p;
}

void del(nodeLE*& graph) {
    nodeLE *p = graph;
    graph = graph->next;
    delete p;
}

void addSorted(nodeLE*& graph, int from, int dest, int weight) {
    add(graph, -1, -1, -1);
    nodeLE *p = graph;
    while (p && p->next) {
        if (weight < p->next->weight) break;
        p = p->next;
    }
    add(p->next, from, dest, weight);
    del(graph);
}

void BellmanFord(nodeLE*& graph, int nodes, int start) {
    int* distances = new int[nodes]{};
    for (int i = 0; i < nodes; i++) {
        distances[i] = INT_MAX;
    }
    distances[start] = 0;
    for (int i = 0; i < nodes - 1; i++) {
        nodeLE* p = graph;
        while (p) {
            int u = p->from;
            int v = p->dest;
            if (distances[u] != INT_MAX && distances[u] + p->weight < distances[v]) {
                distances[v] = distances[u] + p->weight;
            }
            p = p->next;
        }
    }
    nodeLE* p = graph;
    while (p) {
        int u = p->from;
        int v = p->dest;
        if (distances[u] != INT_MAX && distances[u] + p->weight < distances[v]) {
            std::cout << "Graph has a cycle." << std::endl;
            return;
        }
        p = p->next;
    }
    for (int i = 0; i < nodes; i++) {
        std::cout << distances[i] << ' ';
    }
    std::cout << std::endl;
    return;
}

int main() {
    nodeLE* graph = nullptr;
    std::cout << "nodes: ";
    int nodes;
    std::cin >> nodes;
    std::cout << "edges: ";
    int edges;
    std::cin >> edges;
    std::cout << "graph:\n";
    for (int i = 0; i < edges; i++) {
        int from, dest, weight;
        std::cin >> from;
        std::cin >> dest;
        std::cin >> weight;
        add(graph, from, dest, weight);
    }
    nodeLE* p = graph;
    std::cout << std::endl << std::endl;
    while (p) {
        std::cout << p->from << ' ' << p->dest << ' ' << p->weight << std::endl;
        p = p->next;
    }
    BellmanFord(graph, nodes, 0);
}