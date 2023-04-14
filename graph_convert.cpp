#include <iostream>
#include <fstream>

struct nodeLN {
    int dest;
    int weight;
    nodeLN *next;
};

struct nodeLE {
    int source;
    int dest;
    int weight;
    nodeLE *next;
};

void add_to_LN(nodeLN *&LN, int dest, int weight) {
    nodeLN *p = new nodeLN;
    p->dest = dest;
    p->weight = weight;
    p->next = LN;
    LN = p;
}

void add_to_LE(nodeLE *&LE, int source, int dest, int weight) {
    nodeLE *p = new nodeLE;
    p->source = source;
    p->dest = dest;
    p->weight = weight;
    p->next = LE;
    LE = p;
}

void pop_LE(nodeLE *&LE) {
    nodeLE *p = LE;
    LE = LE->next;
    delete p;
}

void init_LN(nodeLN **&LN, int size) {
    LN = new nodeLN *[size];
    for (int i = 0; i < size; i++) {
        LN[i] = NULL;
    }
}

int file_to_LN(std::string filename, nodeLN **&LN) {
    int size;
    std::fstream filecontents;
    filecontents.open(filename);
    filecontents >> size;
    init_LN(LN, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int get_int;
            filecontents >> get_int;
            if (get_int != 0) {
                add_to_LN(LN[i], j, get_int);
            }
        }
    }
    filecontents.close();
    return size;
}

void show_LN(nodeLN **LN, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << "LN" << i <<"->";
        nodeLN *printed = LN[i];
        while(printed) {
            std::cout << '[' << printed->dest << ", " << printed->weight << ']' << "->";
            printed = printed->next;
        }
        std::cout << "NULL" << std::endl;
    }
}

void show_LE(nodeLE *LE) {
    std::cout << "LE->";
    nodeLE *printed = LE;
    while(printed) {
        std::cout << '[' << printed->source << ',' << printed->dest << ',' << printed->weight << ']' << "->";
        printed = printed->next;
    }
    std::cout << "NULL" << std::endl;
}

void delete_list(nodeLE *&LE) {
    if (LE->next) {
        delete_list(LE->next);
    }
    delete LE;
    LE = NULL;
}

void delete_list(nodeLN *&LN) {
    if (LN->next) {
        delete_list(LN->next);
    }
    delete LN;
    LN = NULL;
}

void delete_list(nodeLN **&LN, int size) {
    for (int i = 0; i < size; i++) {
        delete_list(LN[i]);
    }
    delete[] LN;
    LN = NULL;
}

int maxLN(nodeLN **LN, int size) {
    int max = LN[0]->weight;
    for (int i = 0; i < size; i++) {
        nodeLN *p = LN[i];
        while (p) {
            if (p->weight > max) {
                max = p->weight;
            }
            p = p->next;
        }
    }
    return max;
}

nodeLE *prim(nodeLN **LN, int size, int start) {
    int* color = new int[size]{};
    nodeLE *result = NULL;
    add_to_LE(result, -1, -1, -1);
    nodeLE *last = result;
    color[start] = 1;
    for (int j = 0; j < size-1; j++) {
        int min = maxLN(LN, size);
        int source = -1;
        int dest = -1;
        for (int i = 0; i < size; i++) {
            if (color[i] == 0) continue;
            nodeLN *p = LN[i];
            while (p) {
                if (color[p->dest] == 1) {
                    p = p->next;
                    continue;
                }
                if (p->weight >= min) {
                    p = p->next;
                    continue;
                }
                min = p->weight;
                source = i;
                dest = p->dest;
            }
        }
        if (dest > -1) {
            color[dest] = 1;
            add_to_LE(last->next, source, dest, min);
            last = last->next;
        }
    }
    pop_LE(result);
    return result;
}

void Swap(nodeLE *&head) {
    nodeLE *p = head;
    head = head->next;
    p->next = head->next;
    head->next = p;
}

void Bubble_Sort(nodeLE *&head) {
    add_to_LE(head, -1, -1, -1);
    nodeLE *sent = head;
    nodeLE *p = head;
    int count = 0;
    int last_swap = 0;
    int last_swap_prev = 0;
    do {
        count = 0;
        last_swap = 0;
        while (p && p->next && p->next->next) {
            count++;
            if (count == last_swap_prev) break;
            if (p->next->weight > p->next->next->weight) {
                Swap(p->next);
                last_swap = count;
            }
            p = p->next;
        }
        last_swap_prev = last_swap;
        p = head;
    } while (last_swap != 0);
    head = head->next;
    pop_LE(sent);
}

void conv(nodeLN **LN, int size, nodeLE *&LE) {
    nodeLN **cpLN = LN;
    for (int i = 0; i < size; i++) {
        nodeLN *p = cpLN[i];
        while (p) {
            add_to_LE(LE, i, p->dest, p->weight);

            p = p->next;
        }
    }
    Bubble_Sort(LE);
}

int main() {
    nodeLN **LN = NULL;
    int size = file_to_LN("graf0206.txt", LN);
    show_LN(LN, size);
    nodeLE *converted = NULL;
    conv(LN, size, converted);
    result = prim(LN, size, 2);
    show_LE(converted);
    delete_list(LN, size);
    delete_list(converted);
}