//
// Created by dany9 on 29/03/2023.
//

#ifndef IOTSECURITY_VISIBILITYMATRIX_H
#define IOTSECURITY_VISIBILITYMATRIX_H


class VisibilityMatrix {

private:
    int x,y,z;

public:
    VisibilityMatrix(int x, int y, int z);

    int getX() const;

    int getY() const;

    int getZ() const;
};


#endif //IOTSECURITY_VISIBILITYMATRIX_H
