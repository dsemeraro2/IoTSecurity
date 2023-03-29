#ifndef IOTSECURITY_VISIBILITYMATRIX_H
#define IOTSECURITY_VISIBILITYMATRIX_H

#include <iostream>
#include <vector>

class VisibilityMatrix {
private:
    int n, m, t;
    int*** data;
public:
    VisibilityMatrix(int n, int m, int t);

    // Restituisce l'elemento della matrice alle coordinate (n,m,t)
    // O per modificare l'elemento ennesimo
    //int& operator()(int n, int m, int t) {
    //    return data[n][m][t];
    //}

    int getN() const;

    int getM() const;

    int getT() const;

};


#endif //IOTSECURITY_VISIBILITYMATRIX_H
