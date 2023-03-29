#include <iostream>

int newMatrix(int n, int m, int t) {

    int visibilityMatrix[n][m][t];

    for(int i=0; i<n; i++){
        //std::cout << "\ni:" << i;
        std::cout << "\nLayer " << i+1;
        for(int j=0; j<m; j++){
            //std::cout << "j:" << j;
            std::cout << "\n";
            for(int k=0; k<t; k++){
                //std::cout <<  "k:" << k;
                visibilityMatrix[i][j][k] = i+1;
                std::cout << visibilityMatrix[i][j][k];
            }
        }
    }
    return visibilityMatrix[n][m][t];
}