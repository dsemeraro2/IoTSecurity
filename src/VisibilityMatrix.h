#include <iostream>

int newMatrix(int x, int y, int z) {

    int visibilityMatrix[x][y][z];

    for(int i=0; i<x; i++){
        //std::cout << "\ni:" << i;
        std::cout << "\nLayer " << i+1;
        for(int j=0; j<y; j++){
            //std::cout << "j:" << j;
            std::cout << "\n";
            for(int k=0; k<z; k++){
                //std::cout <<  "k:" << k;
                visibilityMatrix[i][j][k] = i+1;
                std::cout << visibilityMatrix[i][j][k];
            }
        }
    }
    return visibilityMatrix[x][y][z];
}