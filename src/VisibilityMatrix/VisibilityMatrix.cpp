//
// Created by dany9 on 29/03/2023.
//

#include "VisibilityMatrix.h"

VisibilityMatrix::VisibilityMatrix(int n, int m, int t) : n(n), m(m), t(t) {}

int VisibilityMatrix::getN() const {
    return n;
}

int VisibilityMatrix::getM() const {
    return m;
}

int VisibilityMatrix::getT() const {
    return t;
}
