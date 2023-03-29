#include <iostream>
#include "VisibilityMatrix.h"

int main()
{
    std::cout << "Ok\n";
    std::cout << "Prova matrice tridimensionale";


    int x = 5;
    int y = 5;
    int z = 5;

    int matrix[x][y][z];
    matrix[x][y][z]= newMatrix(x,y,z);

    return 0;
}
