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
    p = new nodeLN;
    p->dest = from;
    p->weight = weight;
    p->next = graph[dest];
    graph[dest] = p;
}

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

void show_LE(nodeLE* graph) {
    nodeLE *p = graph;
    std::cout << std::endl << std::endl;
    while (p) {
        std::cout << p->from << ' ' << p->dest << ' ' << p->weight << std::endl;
        p = p->next;
    }
}

void prim(nodeLN **graph, int size, int start) {
    int* visited = new int[size]{};
    visited[start] = 1;
    nodeLN* p = graph[start];
    nodeLE* queue = nullptr;
    nodeLE* res = nullptr;
    while (p) {
        add(queue, start, p->dest, p->weight);
        p = p->next;
    }
    while (queue) {
        int N1 = queue->from;
        int N2 = queue->dest;
        std::cout << N1 << ' ' << N2 << ' ' << queue->weight << std::endl;

        if (visited[N1]) {
            if(visited[N2]) {
                del(queue);
                continue;
            }
            visited[N2] = 1;
            addSorted(res, N1, N2, queue->weight);
            p = graph[N2];
            del(queue);
            while (p) {
                addSorted(queue, N2, p->dest, p->weight);
                p = p->next;
            }
            // show_LE(queue);
        }

        // show_LE(queue);
    }

    queue = res;
    std::cout << std::endl << std::endl;
    while (queue) {
        std::cout << queue->from << ' ' << queue->dest << ' ' << queue->weight << std::endl;
        queue = queue->next;
    }
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
    prim(graph, nodes, 0);
}