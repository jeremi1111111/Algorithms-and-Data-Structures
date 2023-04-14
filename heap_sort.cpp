#include <iostream>

void swap_tab(int n1, int n2, int *tab) {
    int p = tab[n1];
    tab[n1] = tab[n2];
    tab[n2] = p;
}

void heapify(int i, int heapsize, int *tab) {
    int L = 2*i;
    int R = 2*i+1;
    int largest;
    if (L <= heapsize && tab[L] > tab[i])
        largest = L;
    else
        largest = i;
    if (R <= heapsize && tab[R] > tab[largest])
        largest = R;
    if (largest != i) {
        swap_tab(i, largest, tab);
        heapify(largest, heapsize, tab);
    }
}

void build_heap(int heapsize, int *tab) {
    for (int i = heapsize/2; i > 0; i--)
        heapify(i, heapsize, tab);
}

void heap_sort(int size, int *tab) {
    int heapsize = size;
    build_heap(heapsize, tab);
    while (heapsize > 1) {
        swap_tab(1, heapsize, tab);
        heapsize--;
        heapify(1, heapsize, tab);
    }
}

int main() {
    int tab[] = {0, -5, 15, 8, 4, 20, 2, 16, 9, 7};
    heap_sort(9, tab);
    for (int i = 1; i < 10; i++) {
        std::cout << tab[i] << ' ';
    }
    std::cout << std::endl;
}