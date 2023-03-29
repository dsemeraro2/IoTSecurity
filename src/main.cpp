#include <iostream>
#include "VisibilityMatrix/VisibilityMatrix.h"

#define X 5
#define Y 5
#define Z 5

int main()
{
    std::cout << "Ok\n";
    std::cout << "Prova matrice tridimensionale";

    int matrix[X][Y][Z];
    matrix[X][Y][Z]= newMatrix(X,Y,Z);

    return 0;
}
