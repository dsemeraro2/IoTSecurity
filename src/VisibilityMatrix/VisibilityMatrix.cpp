#include "VisibilityMatrix.h"

VisibilityMatrix::VisibilityMatrix(int n, int m, int t) : n(n), m(m), t(t) {
    // Allocazione dinamica della matrice tramite il metodo new
    data = new int**[n];
    for (int i=0; i<n; i++) {
        data[i] = new int*[m];
        for (int j=0; j<m; j++) {
            data[i][j] = new int[t];
            for (int k = 0; k<t; k++) {
                data[i][j][k] = i+1;
            }
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

void VisibilityMatrix::setValue (int x, int y, int z, int value){
    // Controlla se gli indici sono validi
    if (x < 0 || x >= n || y < 0 || y >= m || z < 0 || z >= t) {
        throw std::out_of_range("Indici fuori dal range");
    }
    // Assegna il valore alla posizione specificata
    data[x][y][z] = value;
}

void VisibilityMatrix::showMatrix(){
    for(int i=0;i<n;i++){
        std::cout << "\nLayer" << i+1;
        for(int j=0;j<m;j++){
            std::cout<< "\n";
            for(int k=0;k<t;k++){
                std::cout << data[i][j][j];
            }
        }
    }
}


