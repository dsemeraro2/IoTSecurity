#include <iostream>
#include "VisibilityMatrix/VisibilityMatrix.h"

//n*m*t dove n = numero cluster, m = numero leo satellite, t = durata totale simulazione
#define N 5
#define M 5
#define T 5

int main()
{
    std::cout << "Prova matrice tridimensionale";

    VisibilityMatrix matrix(N,M,T);
    matrix(2, 2, 2);


    return 0;
}
