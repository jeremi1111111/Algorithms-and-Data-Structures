#include <iostream>
using namespace std;

struct tree {
    int val;
    tree *R;
    tree *L;
    tree *up;
};

void insert(tree *&root, int x, tree *up) {
    if (root == NULL) {
        tree *p = new tree;
        p->val = x;
        p->L = NULL;
        p->R = NULL;
        p->up = up;
        root = p;
    }
    else {
        if (x >= root->val) {
            insert(root->R, x, root);
        }
        else {
            insert(root->L, x, root);
        }
    }
}

void in_order(tree *root) {
    if (root->L) {
        in_order(root->L);
    }
    cout << root->val << ' ';
    if (root->R) {
        in_order(root->R);
    }
}

void rot_r(tree *&root) {
    tree *B = root->L;
    root->L = B->R;
    B->R = root;
    root = B;
}

tree *search(tree *root, int x) {
    if (x == root->val) {
        return root;
    }
    else if (x > root->val) {
        return search(root->R, x);
    }
    else if (x < root->val) {
        return search(root->L, x);
    }
    else {
        return NULL;
    }
}

tree *min(tree *root) {
    if (root->L) {
        return min(root->L);
    }
    else return root;
}

tree *max(tree *root) {
    if (root->R) {
        return max(root->R);
    }
    else return root;
}

tree *previous(tree *root) {
    if (root->L) {
        return max(root->L);
    }
    tree *p = root->up;
    while (root->up && root == p->L) {
        root = p;
        p = p->up;
    }
    if (p == root) {
        return NULL;
    }
    else {
        return p;
    }
}

tree *next(tree *root) {
    if (root->R) {
        return min(root->R);
    }
    tree *p = root->up;
    while (p && root == p->R) {
        root = p;
        p = p->up;
    }
    if (p == root) {
        return NULL;
    }
    else {
        return p;
    }
}

void remove(tree *&root) {
    tree *p = root;
    if (root->L == NULL && root->R == NULL) {
        root = NULL;
        delete p;
    }
    else if (root->L && root->R == NULL) {
        p = root;
        root = root->L;
        root->up = p->up;
        delete p;
    }
    else if (root->R && root->L == NULL) {
        p = root;
        root = root->R;
        root->up = p->up;
        delete p;
    }
    else {
        p = root;
        root = next(root);
    }
}

int main() {
    tree *root = NULL;
    insert(root, 10, root);
    insert(root, -10, root);
    insert(root, 20, root);
    insert(root, 30, root);
    insert(root, -20, root);
    insert(root, -15, root);
    insert(root, -13, root);
    insert(root, -8, root);
    insert(root, -5, root);
    insert(root, -6, root);
    insert(root, -2, root);
    remove(root->R->R);
    return 0;
}