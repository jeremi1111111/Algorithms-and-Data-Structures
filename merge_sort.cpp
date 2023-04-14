#include <iostream>
#include <string>
using namespace std;

struct node {
    int value;
    node *next;
};

void Add(node *&head, int val) {
    node *p = new node;
    p->value = val;
    p->next = head;
    head = p;
}

void Add_Tab(node *&head, int *tab, int size) {
    for (int i = size - 1; i >= 0; i--) {
        Add(head, tab[i]);
    }
}

void Del(node *&head) {
    if (head) {
        node *e = head;
        head = head->next;
        delete e;
    }
}

void Show(node *head, string name) {
    cout << name << "->";
    node *printed = head;
    while(printed) {
        cout << printed->value << "->";
        printed = printed->next;
    }
    cout << "NULL" << endl;
}

void Split(node *&head, node *&head1, node *&head2) {
    node *p = head;
    node *e = head;
    while (p && p->next && e && e->next && e->next->next) {
        p = p->next;
        e = e->next->next;
    }
    head2 = p->next;
    p->next = NULL;
    head1 = head;
    head = NULL;
}

void Merge(node *&head, node *&head1, node *&head2) {
    Add(head, 0);
    node *sent = head;
    node *tail = head;
    while (head1 && head2) {
        if (head1->value < head2->value) {
            tail->next = head1;
            head1 = head1->next;
            tail = tail->next;
        }
        else {
            tail->next = head2;
            head2 = head2->next;
            tail = tail->next;
        }
    }
    if (head1) {
        tail->next = head1;
        head1 = NULL;
    }
    else if (head2) {
        tail->next = head2;
        head2 = NULL;
    }
    head = head->next;
    Del(sent);
}

void Merge_Sort(node *&head) {
    node *head1 = NULL;
    node *head2 = NULL;
    if (head->next) {
        Split(head, head1, head2);
        Merge_Sort(head1);
        Merge_Sort(head2);
    }
    Merge(head, head1, head2);
}

int main() {
    node *head = NULL;
    node *head1 = NULL;
    node *head2 = NULL;
    int tab[8] = {3, -8, 2, -6, 12, 4, 7};
    Add_Tab(head, tab, 7);
    Show(head, "H");
    // Split(head, head1, head2);
    // Show(head, "H");
    // Show(head1, "H1");
    // Show(head2, "H2");
    // Merge(head, head1, head2);
    // Show(head, "H");
    Merge_Sort(head);
    Show(head, "H");
}