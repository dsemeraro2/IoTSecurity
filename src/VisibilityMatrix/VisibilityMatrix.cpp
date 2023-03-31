#include "VisibilityMatrix.h"

VisibilityMatrix::VisibilityMatrix(int t, int n, int m) {
    this->tMax = t;
    this->nMax = n;
    this->mMax = m;
    // Allocazione dinamica della matrice tramite il metodo new
    data = new int**[t];
    for (int i=0; i<t; i++) {
        data[i] = new int*[n];
        for (int j=0; j<n; j++) {
            data[i][j] = new int[m];
            for (int k=0; k<m; k++) {
                data[i][j][k] = 0;
            }
        }
    }
}

int VisibilityMatrix::getNMax() const {
    return nMax;
}

int VisibilityMatrix::getMMax() const {
    return mMax;
}

int VisibilityMatrix::getTMax() const {
    return tMax;
}

// Set a value a un'elemento della matrice alle coordinate (tMax,nMax,mMax)
void VisibilityMatrix::setValue (int t, int n, int m, int value){
    // Controlla se gli indici sono validi
    if (t < 0 || t >= tMax || n < 0 || n >= nMax || m < 0 || m >= mMax) {
        throw std::out_of_range("Indici fuori dal range");
    }
    // Assegna il valore alla posizione specificata
    data[t][n][m] = value;
}

void VisibilityMatrix::showMatrix(){
    for(int i=0; i<tMax; i++){
        std::cout << "\nT:" << i;
        for(int j=0;j<nMax;j++){
            std::cout<< "\n";
            for(int k=0;k<mMax;k++){
                std::cout << data[i][j][k] << " ";
            }
        }
    }
}
