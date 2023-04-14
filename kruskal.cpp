#include <iostream>

/*
graph:
weight  from    dest
14        3      5
11        1      7
10        5      4
9         3      4
8         1      2
8         0      7
7         7      8
7         2      3
6         8      6
4         2      5
4         0      1
2         6      5
2         8      2
1         7      6
*/

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

void kruskal(nodeLE* graph, int size) {
    int* forest = new int[size]{};
    nodeLE* p = graph;
    nodeLE* res = nullptr;
    int count = 1;
    while (p) {
        int F1 = forest[p->from];
        int F2 = forest[p->dest];
        if (F1 == 0) {
            if (F2 == 0) {
                forest[p->from] = count;
                forest[p->dest] = count;
                count++;
                add(res, p->from, p->dest, p->weight);
                p = p->next;
                continue;
            }
            forest[p->from] = forest[p->dest];
            add(res, p->from, p->dest, p->weight);
            p = p->next;
            continue;
        }
        if (F2 == 0) {
            forest[p->dest] = forest[p->from];
            add(res, p->from, p->dest, p->weight);
            p = p->next;
            continue;
        }
        if (F1 != F2) {
            for (int i = 0; i < size; i++) {
                if (forest[i] == F2) forest[i] = F1;
            }
            add(res, p->from, p->dest, p->weight);
        }
        p = p->next;
    }

    p = res;
    std::cout << std::endl << std::endl;
    while (p) {
        std::cout << p->from << ' ' << p->dest << ' ' << p->weight << std::endl;
        p = p->next;
    }
}

int main() {
    nodeLE* graph = nullptr;
    std::cout << "size: ";
    int size;
    std::cin >> size;
    std::cout << "graph:\n";
    for (int i = 0; i < size; i++) {
        int from, dest, weight;
        std::cin >> weight;
        std::cin >> from;
        std::cin >> dest;
        addSorted(graph, from, dest, weight);
    }
    nodeLE* p = graph;
    std::cout << std::endl << std::endl;
    while (p) {
        std::cout << p->from << ' ' << p->dest << ' ' << p->weight << std::endl;
        p = p->next;
    }
    kruskal(graph, 9);
}