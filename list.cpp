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

void swap(node *&head) {
    node *p = head;
    head = head->next;
    p->next = head->next;
    head->next = p;
}

void del_closest(node *&head, int x) {
    add(head, -10000);
    node *sent = head;
    node *p = head;
    node *closest = NULL;
    while (p && p->next) {
        if (closest == NULL) {
            closest = p;
            p = p->next;
            continue;
        }
        if (closest->next->value == x) break;
        if (p->next->value == closest->next->value || p->next->value == 2 * x - closest->next->value) {
            p = p->next;
            continue;
        }
        if (closest->next->value < x) {
            if (p->next->value < closest->next->value || p->next->value > 2 * x - closest->next->value) {
                p = p->next;
                continue;
            }
        }
        else if (closest->next->value > x) {
            if (p->next->value > closest->next->value || p->next->value < 2 * x - closest->next->value) {
                p = p->next;
                continue;
            }
        }
        closest = p;
        p = p->next;
    }
    del(closest->next);
    head = head->next;
    del(sent);
}

int main() {
    node *head = NULL;
    int tab[7] = {1, -5, 10, 3, 8, 12, 13};
    add_tab(head, tab, 7);
    show(head);
    del_closest(head, 11);
    show(head);
}