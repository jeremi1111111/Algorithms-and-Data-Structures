#include <iostream>

class tree {
public:
    int val;
    int bal;
    tree * parent;
    tree * left;
    tree * right;
    tree (int, tree *);
};

tree::tree(int v, tree * p) {
    this->val = v;
    this->bal = 0;
    this->parent = p;
    this->left = nullptr;
    this->right = nullptr;
}

void rotRight (tree *& root) {
    tree * p = root->left;
    root->left = p->right;
    if (p->right != nullptr) p->right->parent = p->parent;
    p->right = p->parent;
    p->parent = root->parent;
    root->parent = p;
    root = p;
}

void rotLeft (tree *& root) {
    tree * p = root->right;
    root->right = p->left;
    if (p->left != nullptr) p->left->parent = p->parent;
    p->left = p->parent;
    p->parent = root->parent;
    root->parent = p;
    root = p;
}

void rotLeftRight (tree *& root) {
    rotLeft(root->left);
    rotRight(root);
    return;
}

void rotRightLeft (tree *& root) {
    rotRight(root->right);
    rotLeft(root);
}

tree * search (tree *root, int val) {
    if (val == root->val) {
        return root;
    }
    else if (val > root->val) {
        return search(root->right, val);
    }
    else if (val < root->val) {
        return search(root->left, val);
    }
    else {
        return NULL;
    }
}

tree * min (tree *root) {
    if (root->left) {
        return min(root->left);
    }
    else return root;
}

tree * max (tree *root) {
    if (root->right) {
        return max(root->right);
    }
    else return root;
}

tree * previous (tree * root) {
    if (root->left) {
        return max(root->left);
    }
    tree * p = root->parent;
    while (root->parent && root == p->left) {
        root = p;
        p = p->parent;
    }
    if (p == root) {
        return NULL;
    }
    else {
        return p;
    }
}

tree * next (tree * root) {
    if (root->right) {
        return min(root->right);
    }
    tree * p = root->parent;
    while (p && root == p->right) {
        root = p;
        p = p->parent;
    }
    if (p == root) {
        return NULL;
    }
    else {
        return p;
    }
}

int add (tree *& root, int val, tree * parent = nullptr) {
    int added = 0;

    if (root == nullptr) {
        root = new tree (val, parent);
        added = 1;
        return 1;
    }

    if (val <= root->val) {
        added = add (root->left, val, root);
        if (added == 1) root->bal -= 1; 
    }
    else {
        added = add (root->right, val, root);
        if (added == 1) root->bal += 1;
    }

    if (root->bal == -2) {
        if (root->left->bal == -1) {
            rotRight(root);
            root->bal = 0;
            root->right->bal = 0;
        }
        else if (root->left->bal == 1) {
            rotLeftRight(root);
            if (root->bal == -1) {
                root->left->bal = 0;
                root->right->bal = 1;
            }
            else if (root->bal == 1) {
                root->left->bal = -1;
                root->right->bal = 0;
            }
            root->bal = 0;
        }
        added = 0;
    }
    else if (root->bal == 2) {
        if (root->right->bal == 1) {
            rotLeft(root);
            root->bal = 0;
            root->left->bal = 0;
        }
        else if (root->right->bal == -1) {
            rotRightLeft(root);
            if (root->bal == -1) {
                root->left->bal = 0;
                root->right->bal = 1;
            }
            else if (root->bal == 1) {
                root->left->bal = -1;
                root->right->bal = 0;
            }
            root->bal = 0;
        }
        added = 0;
    }
    else if (root->bal == 0) added = 0;

    return added;
}

void removebst (tree *& root, tree * del) {
    if (root == nullptr) return;
    tree * p = del;
    if (del->right && del->left) p = next(del);
    tree * n = p->left;
    if (p->right) n = p->right;
    if (n) n->parent = p->parent;
    if (p->parent) {
        if (p->parent->left == p) p->parent->left = n;
        p->parent->right = n;
    }
    else root = n;
    if (p != del) del->val = p->val;
    delete p;
}

// almost works, balances are wrong
void remove (tree *& root, tree * del) {
    if (root == nullptr) return;
    tree * p = del;
    if (del->right && del->left) p = next(del);
    tree * n = p->left;
    if (p->right) n = p->right;
    if (n) n->parent = p->parent;
    if (p->parent) {
        if (p->parent->left == p) p->parent->left = n;
        p->parent->right = n;
    }
    else root = n;
    if (p != del) del->val = p->val;
    delete p;

    if (root == nullptr) return;

    if (n) p = n->parent;
    else if (del) p = del;
    while (p) {
        if (p->left == n) p->bal += 1;
        else if (p->right == n) p->bal -= 1;

        if (p->bal == -1 || p->bal == 1) break;

        if (p->bal == -2) {
            if (p->left->bal == -1 || p->left->bal == 0) {
                rotRight(p);
                if (p->bal == 0) {
                    p->bal = 1;
                    p->right->bal = -1;
                }
                else {
                    p->bal = 0;
                    p->right->bal = 0;
                }
            }
            else {
                rotLeftRight(p);
                if (p->bal == -1) {
                    p->left->bal = 0;
                    p->right->bal = 1;
                }
                else if (p->bal == 1) {
                    p->left->bal = -1;
                    p->right->bal = 0;
                }
                p->bal = 0;
            }
            if (p->right == root) root = p;
        }
        else if (p->bal == 2) {
            if (p->right->bal == 1 || p->right->bal == 0) {
                rotLeft(p);
                if (p->bal == 0) {
                    p->bal = -1;
                    p->left->bal = 1;
                }
                else {
                    p->bal = 0;
                    p->left->bal = 0;
                }
            }
            else {
                rotRightLeft(p);
                if (p->bal == -1) {
                    p->left->bal = 0;
                    p->right->bal = 1;
                }
                else if (p->bal == 1) {
                    p->left->bal = -1;
                    p->right->bal = 0;
                }
                p->bal = 0;
            }
            if (p->left == root) root = p;
        }

        n = p;
        p = p->parent;
    }
}

int main() {
    tree * T1 = nullptr;
    int nums = 0;
    std::cout << "How many nums?: ";
    std::cin >> nums;
    std::cout << "Input numbers: ";
    for (int i = 0; i < nums; i++) {
        int num;
        std::cin >> num;
        add (T1, num);
    }
    int del;
    std::cout << "What to delete?: ";
    std::cin >> del;

    tree *toDel = search(T1, del);
    if (toDel != nullptr) remove(T1, toDel);
    return 0;
}