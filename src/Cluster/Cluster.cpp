#include "Cluster.h"

Cluster::Cluster(int id, Service **service) : id(id), service(service) {
    this->id = id;
    for(int i=0; i<MAXSERVICES; i++){
        this->service[i] = service[i];
    }
}