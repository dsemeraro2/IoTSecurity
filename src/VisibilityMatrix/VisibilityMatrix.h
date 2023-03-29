//
// Created by dany9 on 29/03/2023.
//

#ifndef IOTSECURITY_VISIBILITYMATRIX_H
#define IOTSECURITY_VISIBILITYMATRIX_H


class VisibilityMatrix {
private:
    int n, m, t;
public:
    VisibilityMatrix(int n, int m, int t);

    int getN() const;

    int getM() const;

    int getT() const;
};


#endif //IOTSECURITY_VISIBILITYMATRIX_H
