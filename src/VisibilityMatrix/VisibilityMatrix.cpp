#include "VisibilityMatrix.h"

VisibilityMatrix::VisibilityMatrix(int x, int y, int z) : x(x), y(y), z(z) {}

int VisibilityMatrix::getX() const {
    return x;
}

int VisibilityMatrix::getY() const {
    return y;
}

int VisibilityMatrix::getZ() const {
    return z;
}
