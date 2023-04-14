#include <iostream>

void calcPreSufTab(std::string pattern, int psTab[]) {
    // starting from index 0
    int pattlen = pattern.length();
    psTab[0] = 0;
    int pattindex = 0;
    for (int i = 1; i < pattlen; i++) {
        while (pattindex > 0 && pattern[pattindex] != pattern[i]) pattindex = psTab[pattindex-1];
        if (pattern[pattindex] == pattern[i]) pattindex = pattindex + 1;
        psTab[i] = pattindex;
    }
    for (int i = 0; i < pattlen; i++) {
        std::cout << psTab[i] << ' ';
    }

/* starting from index 1
    psTab[1] = 0;
    int k = 0;
    for (int q = 2; q < m; q++) {
        while (k > 0 && pattern[k+1] != pattern[q]) k = psTab[k];
        if (pattern[k+1] == pattern[q]) k = k + 1;
        psTab[q] = k;
    }
    for (int i = 1; i < m; i++) {
        std::cout << psTab[i] << ' ';
    }
*/
}
 
void kmpAlgorithm(std::string text, std::string pattern) {
    int textlen = text.length();
    int pattlen = pattern.length();
    int* psTab = new int[pattlen]{};
    calcPreSufTab(pattern, psTab);
    int pattindex = 0;
    for (int i =  0; i < textlen; i++) {
        while (pattindex > 0 && pattern[pattindex] != text[i]) pattindex = psTab[pattindex-1];
        if (pattern[pattindex] == text[i]) pattindex = pattindex + 1;
        if (pattindex == pattlen) {
            std::cout << "Wzorzec wystepuje na pozycji " << i - pattlen + 1 << std::endl;
            pattindex = psTab[pattindex-1];
        }
    }
}

int main() {
    std::string text = "BCDABACDABABCDABABC";
    // std::string pattern = "ABC";
    std::string pattern = "rabrabcdg";
    // kmpAlgorithm(text, pattern);
    int psTab[10] = {};
    calcPreSufTab(pattern, psTab);
}