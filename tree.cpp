#include <iostream>

struct tree {
    int val;
    tree *left;
    tree *right;
    tree *up;
};

void insert(tree *&root, int val, tree *up) {
    if (root == NULL) {
        tree *p = new tree;
        p->val = val;
        p->left = NULL;
        p->right = NULL;
        p->up = up;
        root = p;
    }
    else {
        if (val >= root->val) {
            insert(root->right, val, root);
        }
        else {
            insert(root->left, val, root);
        }
    }
}

void tabInsert(tree *&root, int *tab, int size, tree *up) {
    for (int i = 0; i < size; i++) {
        insert(root, tab[i], up);
    }
}

void inOrder(tree *root) {
    if (root->left) {
        inOrder(root->left);
    }
    std::cout << root->val << ' ';
    if (root->right) {
        inOrder(root->right);
    }
}

tree *minVal(tree *root) {
    if (root->left) {
        return minVal(root->left);
    }
    else return root;
}

tree *maxVal(tree *root) {
    if (root->right) {
        return maxVal(root->right);
    }
    else return root;
}

tree *nextVal(tree *root) {
    if (root->right) {
        return minVal(root->right);
    }
    tree *p = root->up;
    while (p && root == p->right) {
        root = p;
        p = p->up;
    }
    return p;
}

tree *prevVal(tree *root) {
    if (root->left) {
        return maxVal(root->left);
    }
    tree *p = root->up;
    while (p && root == p->left) {
        root = p;
        p = p->up;
    }
    return p;
}

void removeRoot(tree *&root) {
    tree *replace;
    if (root->left && root->right) replace = nextVal(root);
    else replace = root;
    tree *p;
    if (replace->left) p = replace->left;
    else p = replace->right;
    if (p) p->up = replace->up;
    if (replace->up) {
        if (replace == replace->up->left) replace->up->left = p;
        else replace->up->right = p;
    }
    else root = p;
    if (root != p && replace != root) root->val = replace->val;
    delete replace;
}

void removeLeaves(tree *&root) {
    if (!root->left && !root->right) {
        tree *p = root;
        root = NULL;
        delete p;
    }
    else {
        if (root->left) removeLeaves(root->left);
        if (root->right) removeLeaves(root->right);
    }
}

void rotateTreeRight(tree *&root) {
    tree *p = root;
    tree *replace = root->left;
    if (!replace) return; 
    p->left = replace->right;
    if (p->left) {
        p->left->up = p;
    }
    replace->up = p->up;
    replace->right = p;
    p->up = replace;
    root = replace;
}

void rotateTreeLeft(tree *&root) {
    tree *p = root;
    tree *replace = root->right;
    if (!replace) return;
    p->right = replace->left;
    if (p->right) {
        p->right->up = p;
    }
    replace->up = p->up;
    replace->left = p;
    p->up = replace;
    root = replace;
}

int main() {
    tree *root = NULL;
    // int tab[13] = {10, -10, 20, 30, -20, -15, -13, -8, -5,  -6, -2, -21, -22};
    // int tab[] = {15, 5, 3, 12, 10, 13, 6, 7, 16, 20, 18, 23};
    // int tab[] = {10, 5, 20, 4, 8, 15, 22, 6, 9, 7};
    int tab[] = {10, 5, 20, 3, 15, 25};
    tabInsert(root, tab, 6, root);
    inOrder(root);
    std::cout << std::endl;
    removeRoot(root);
    // removeLeaves(root);
    // rotateTreeRight(root);
    // rotateTreeLeft(root);
    inOrder(root);
    std::cout << std::endl;
    // std::cout << previous(root->left->left)->val << std::endl;
    // std::cout << "min root: " << minVal(root)->val << std::endl;
    // std::cout << "max root: " << maxVal(root)->val << std::endl;
    // std::cout << "min root->right: " << minVal(root->right)->val << std::endl;
    // std::cout << "max root->left: " << maxVal(root->left)->val << std::endl;
    return 0;
}