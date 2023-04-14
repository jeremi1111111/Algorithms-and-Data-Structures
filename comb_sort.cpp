#include <iostream>

struct node {
    int value;
    node *next;
};

void add(node *&head, int val) {
    node *p = new node;
    p->value = val;
    p->next = head;
    head = p;
}

void add_tab(node *&head, int *tab, int size) {
    for (int i = size - 1; i >= 0; i--) {
        add(head, tab[i]);
    }
}

void show(node *head) {
    std::cout << "H->";
    node *printed = head;
    while(printed) {
        std::cout << printed->value << "->";
        printed = printed->next;
    }
    std::cout << "NULL" << std::endl;
}

void del(node *&head) {
    if (head) {
        node *e = head;
        head = head->next;
        delete e;
    }
}

void swap_x_y(node *&swap_1, node *&swap_2) {
    node *p = swap_1->next;
    swap_1->next = swap_2->next;
    swap_2->next = p;
    p = swap_2;
    swap_2 = swap_1;
    swap_1 = p;
}

void swap(node *&head) {
    node *p = head;
    head = head->next;
    p->next = head->next;
    head->next = p;
}

void bubble_sort(node *&head) {
    add(head, -1);
    node *sent = head;
    node *p = head;
    int count = 0;
    int last_swap = 0;
    int last_swap_prev = 0;
    do {
        count = 0;
        last_swap = 0;
        while (p && p->next && p->next->next) {
            count++;
            if (count == last_swap_prev) break;
            if (p->next->value > p->next->next->value) {
                swap(p->next);
                last_swap = count;
            }
            p = p->next;
        }
        last_swap_prev = last_swap;
        p = head;
    } while (last_swap != 0);
    head = head->next;
    del(sent);
}

void comb_sort(node *&head, int gap) {
    gap = gap*10/13;
    if (gap == 10 || gap == 9) gap = 11;
    if (gap == 0) gap = 1;
    if (gap == 1) {
        bubble_sort(head);
        return;
    }
    add(head, 0);
    node *sent = head;
    node *p = head;
    node *e = head;
    for (int i = gap; i > 0; i--) {
        e = e->next;
    }
    while (e->next) {
        if (p->next->value > e->next->value) swap_x_y(p->next, e->next);
        p = p->next;
        e = e->next;
    }
    head = head->next;
    del(sent);
    comb_sort(head, gap);
}

int main() {
    node *head = NULL;
    int tab[15] = {-8, 12, -3, 4, 5, 11, 13, 19, -20, 0, 7, 17, -8, 14, 6};
    add_tab(head, tab, 15);
    show(head);
    comb_sort(head, 15);
    show(head);
}