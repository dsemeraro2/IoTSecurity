#include "Constellation.h"

Constellation::Constellation(int mMax) {
    this->mMax = mMax;

    for (int i = 0; i < mMax; i++) {
        Satellite satellite{i, 2000000 * 64, 64};
        this->satellaties.push_back(satellite);
    }

}
