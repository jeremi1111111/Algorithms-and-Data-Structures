#include <iostream>
#include <time.h>

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

void add_rand(node *&head, int count) {
    for (int i = count; i > 0; i--) {
        add(head, rand() % 100);
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

int main() {
    srand(time(NULL));
    node *head = NULL;
    add_rand(head, 20);
    show(head);
    bubble_sort(head);
    show(head);
}