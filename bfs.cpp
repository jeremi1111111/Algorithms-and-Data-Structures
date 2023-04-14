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

void bfs(nodeLN** graph, int nodes, int start) {
    int* visited = new int[nodes]{};
    int* order = new int[nodes]{};
    order[0] = start;
    int count = 1;
    // for (int i = 0; i < nodes-1; i++) {
    //     visited[order[i]] = true;
    //     nodeLN* p = graph[order[i]];
    //     while (p) {
    //         if (visited[p->dest] == false) {
    //             order[count] = p->dest;
    //             count++;
    //         }
    //         p = p->next;
    //     }
    // }
    for (int i = 0; i < nodes; i++) {
        visited[order[i]] = 2;
        nodeLN* p = graph[order[i]];
        while (p) {
            if (visited[p->dest] == 0) {
                order[count] = p->dest;
                visited[p->dest] = 1;
                count++;
            }
            if (count >= nodes) break;
            p = p->next;
        }
        if (count >= nodes) break;
    }
    for (int i = 0; i < nodes; i++) {
        std::cout << order[i] << ' ';
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
    bfs(graph, nodes, 0);
}