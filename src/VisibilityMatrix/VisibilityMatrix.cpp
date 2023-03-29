#include "VisibilityMatrix.h"

VisibilityMatrix::VisibilityMatrix(int n, int m, int t) : n(n), m(m), t(t) {
    // Allocazione dinamica della matrice
    data = new int**[n];
    for (int i = 0; i < n; ++i) {
        data[i] = new int*[m];
        for (int j = 0; j < m; ++j) {
            data[i][j] = new int[t];
        }
    }
}

int VisibilityMatrix::getN() const {
    return n;
}

int VisibilityMatrix::getM() const {
    return m;
}

int VisibilityMatrix::getT() const {
    return t;
}

