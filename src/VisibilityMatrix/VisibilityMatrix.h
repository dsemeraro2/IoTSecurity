#ifndef IOTSECURITY_VISIBILITYMATRIX_H
#define IOTSECURITY_VISIBILITYMATRIX_H

#include <iostream>
#include <vector>


//tMax = timeSlot
//nMax = cluster = servizio
//mMax = satellite
class VisibilityMatrix {
private:
    int tMax, nMax, mMax;
    int ***data;
public:
    VisibilityMatrix(int t, int n, int m);

    // Restituisce l'elemento della matrice alle coordinate (tMax,nMax,mMax)


    int getNMax() const;

    int getMMax() const;

    int getTMax() const;

    // Restituisce l'elemento della matrice alle coordinate (tMax,nMax,mMax)
    int getValue(int t, int n, int m);

    // Set a value a un'elemento della matrice alle coordinate (tMax,nMax,mMax)
    void setValue(int t, int n, int m, int value);

    // Mostra tutta la matrice
    void showMatrix();

    void initialize();

};


#endif //IOTSECURITY_VISIBILITYMATRIX_H
