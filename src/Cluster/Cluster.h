#ifndef IOTSECURITY_CLUSTER_H
#define IOTSECURITY_CLUSTER_H


#include "../Service/Service.h"

class Cluster {

private:

    int id;
    Service *service[];

public:
    Cluster(int id, Service **service);

};


#endif //IOTSECURITY_CLUSTER_H
