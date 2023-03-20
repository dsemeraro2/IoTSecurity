// C++ program to rotate a matrix
#include <bits/stdc++.h>
#define R 5
#define C 5
using namespace std;
// A function to rotate a matrix mat[][] of size R x C.
// Initially, m = R and n = C
void rotatematrix(int m, int n, char mat[R][C])
{
    int row = 0, col = 0;
    int prev, curr;

    /*
    row - Starting row index
    m - ending row index
    col - starting column index
    n - ending column index
    i - iterator
    */
    while (row < m && col < n)
    {
        if (row + 1 == m || col + 1 == n)
            break;

        // Store the first element of next row, this
        // element will replace first element of current
        // row
        prev = mat[row + 1][col];

        /* Move elements of first row from the remaining rows */
        for (int i = col; i < n; i++)
        {
            curr = mat[row][i];
            mat[row][i] = prev;
            prev = curr;
        }
        row++;

        /* Move elements of last column from the remaining columns */
        for (int i = row; i < m; i++)
        {
            curr = mat[i][n-1];
            mat[i][n-1] = prev;
            prev = curr;
        }
        n--;

        /* Move elements of last row from the remaining rows */
        if (row < m)
        {
            for (int i = n-1; i >= col; i--)
            {
                curr = mat[m-1][i];
                mat[m-1][i] = prev;
                prev = curr;
            }
        }
        m--;

        /* Move elements of first column from the remaining rows */
        if (col < n)
        {
            for (int i = m-1; i >= row; i--)
            {
                curr = mat[i][col];
                mat[i][col] = prev;
                prev = curr;
            }
        }
        col++;
    }

    // Print rotated matrix
    for (int i=0; i<R; i++)
    {
        for (int j=0; j<C; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

/* Driver program to test above functions */
int main()
{
    char satellite[R][C] = { {'*', '*', '*', '*', '*'},
                     {'S', ' ', ' ', ' ', '*'},
                     {'*', ' ', 'E', ' ', '*'},
                     {'*', ' ', ' ', ' ', '*'},
                     {'*', '*', '*', '*', '*'} };

    for(int i=0; i<16; i++){
        cout << "\n";
        rotatematrix(R, C, satellite);
    }
    return 0;
}
