#include "Constellation.h"

Constellation::Constellation(int mMax) {
    this->mMax = mMax;

    for (int i = 0; i < mMax; i++) {
        Satellite satellite{i, 30, 30};
        this->satellaties.push_back(satellite);
    }

}
