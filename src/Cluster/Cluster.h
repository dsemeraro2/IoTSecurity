#ifndef IOTSECURITY_CLUSTER_H
#define IOTSECURITY_CLUSTER_H

#include <vector>
#include "../Service/Service.h"

class Cluster {

private:

    int id;
    std::vector<Service> services;

public:
    Cluster(int id, std::vector<Service> service);

    int getId() const;

    const std::vector<Service> &getServices() const;

};


#endif //IOTSECURITY_CLUSTER_H
