#ifndef IOTSECURITY_VISIBILITYMATRIX_H
#define IOTSECURITY_VISIBILITYMATRIX_H

#include <iostream>
#include <vector>

class VisibilityMatrix {
private:
    int tMax, nMax, mMax;
    int*** data;
public:
    VisibilityMatrix(int t, int n, int m);

    // Restituisce l'elemento della matrice alle coordinate (tMax,nMax,mMax)
    int& operator()(int t, int n, int m) {
        return data[t][n][m];
    }

    int getNMax() const;

    int getMMax() const;

    int getTMax() const;

    // Set a value a un'elemento della matrice alle coordinate (tMax,nMax,mMax)
    void setValue (int t, int n, int m, int value);

    // Mostra tutta la matrice
    void showMatrix();

    void initialize();

};


#endif //IOTSECURITY_VISIBILITYMATRIX_H
