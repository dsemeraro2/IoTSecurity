#ifndef IOTSECURITY_CLUSTER_H
#define IOTSECURITY_CLUSTER_H

#include <vector>
#include "../Service/Service.h"

class Cluster {

private:
    int id;

public:
    Cluster(int id);

    int getId() const;

};


#endif //IOTSECURITY_CLUSTER_H
