#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct node {
    int index;
    int weight;
    node *next;
};

void add_to_LS(node *&LS, int index, int weight) {
    node *p = new node;
    p->index = index;
    p->weight = weight;
    p->next = LS;
    LS = p;
}

void init_MS(int **&MS, int size) {
    MS = new int *[size];
    for (int i = 0; i < size; i++) {
        MS[i] = new int[size];
        for (int j = 0; j < size; j++) {
            MS[i][j] = 0;
        }
    }
}

int file_to_MS(string filename, int **&MS) {
    int size;
    fstream filecontents;
    filecontents.open(filename);
    filecontents >> size;
    init_MS(MS, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int newnum;
            filecontents >> newnum;
            MS[i][j] = newnum;
        }
    }
    filecontents.close();
    return size;
}

void init_LS(node **&LS, int size) {
    LS = new node *[size];
    for (int i = 0; i < size; i++) {
        LS[i] = NULL;
    }
}

int file_to_LS(string filename, node **&LS) {
    int size;
    fstream filecontents;
    filecontents.open(filename);
    filecontents >> size;
    init_LS(LS, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int get_int;
            filecontents >> get_int;
            if (get_int != 0) {
                add_to_LS(LS[i], j, get_int);
            }
        }
    }
    filecontents.close();
    return size;
}

int init_LK(int **&LK, int size) {
    LK = new int *[size];
    for (int i = 0; i < size; i++) {
        LK[i] = new int[3];
        for (int j = 0; j < 3; j++) {
            LK[i][j] = 0;
        }
    }
}

int file_to_LK(string filename, int **&LK) {
    int size;
    fstream filecontents;
    filecontents.open(filename);
    filecontents >> size;
    init_LK(LK, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 3; j++) {
            int newnum;
            filecontents >> newnum;
            LK[i][j] = newnum;
        }
    }
    filecontents.close();
    return size;
}

void print_matrix(int **MS, int matrixsize) {
    for (int i = 0; i < matrixsize; i++) {
        for (int j = 0; j < matrixsize; j++) {
            cout << MS[i][j] << ' ';
        }
        cout << endl;
    }
}

void print_matrix(int **MS, int matrixrows, int matrixcols) {
    for (int i = 0; i < matrixrows; i++) {
        for (int j = 0; j < matrixcols; j++) {
            cout << MS[i][j] << ' ';
        }
        cout << endl;
    }
}

void show_list(node **LS, int listsize) {
    for (int i = 0; i < listsize; i++) {
        cout << "H" << i <<"->";
        node *printed = LS[i];
        while(printed) {
            cout << '[' << printed->index << ", " << printed->weight << ']' << "->";
            printed = printed->next;
        }
        cout << "NULL" << endl;
    }
}

void delete_matrix(int **&MS, int matrixrows) {
    for (int i = 0; i < matrixrows; i++) {
        delete[] MS[i];
    }
    delete[] MS;
    MS = NULL;
}

void delete_list(node *&LS) {
    if (LS->next) {
        delete_list(LS->next);
    }
    delete LS;
    LS = NULL;
}

void delete_list(node **&LS, int listsize) {
    for (int i = 0; i < listsize; i++) {
        delete_list(LS[i]);
    }
    delete[] LS;
    LS = NULL;
}

int MS_to_LS(int **MS, node **&LS, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (MS[i][j] != 0) {
                add_to_LS(LS[i], j, MS[i][j]);
            }
        }
    }
    return size;
}

int LS_to_MS(node **LS, int **&MS, int size) {
    for (int i = 0; i < size; i++) {
        node *p = LS[i];
        while (p) {
            MS[i][p->index] = p->weight;
            p = p->next;
        }
    }
    return size;
}

int MS_to_LK(int **MS, int **&LK, int size) {

}

int main() {
    int **MS;
    int MSsize = 0;
    MSsize = file_to_MS("graf.txt", MS);
    print_matrix(MS, MSsize);
    int **LK;
    init_LK(LK, MSsize);
    int LKsize = MS_to_LK(MS, LK, MSsize);
    print_matrix(LK, LKsize);
    delete_matrix(MS, MSsize);
    delete_matrix(LK, LKsize);

    // cout << endl;

    // node **LS;
    // int LSsize = 0;
    // LSsize = file_to_LS("graf.txt", LS);
    // show_list(LS, LSsize);
    // int **MS;
    // init_MS(MS, LSsize);
    // int MSsize = LS_to_MS(LS, MS, LSsize);
    // print_matrix(MS, MSsize);
    // delete_list(LS, LSsize);
    // delete_matrix(MS, MSsize);

    // cout << endl;

    // int **LK;
    // int LKsize = 0;
    // LKsize = file_to_LK("graflk.txt", LK);
    // print_matrix(LK, LKsize, 3);
    // delete_matrix(LK, LKsize);

    return 0;
}