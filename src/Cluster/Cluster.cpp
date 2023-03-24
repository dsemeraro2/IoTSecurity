#include "Cluster.h"

Cluster::Cluster(int id, std::vector<Service> services) : id(id), services(services) {
    this->id = id;
    this->services = services;
}

int Cluster::getId() const {
    return id;
}

const std::vector<Service> &Cluster::getServices() const {
    return services;
}
