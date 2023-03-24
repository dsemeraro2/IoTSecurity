#ifndef IOTSECURITY_CLUSTER_H
#define IOTSECURITY_CLUSTER_H

#define MAXSERVICES 3
#include "../Service/Service.h"

class Cluster {

private:

    int id;
    Service *service[MAXSERVICES];

public:
    Cluster(int id, Service **service);

};


#endif //IOTSECURITY_CLUSTER_H
