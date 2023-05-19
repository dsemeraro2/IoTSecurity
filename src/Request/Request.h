#ifndef IOTSECURITY_REQUEST_H
#define IOTSECURITY_REQUEST_H

#include <iostream>
#include <vector>
#include "../Service/Service.h"

typedef int timeSlot;

class Request {

    int idRequest;
    int idCluster{};
    timeSlot tsGenerate{};
    timeSlot tsDeadline{};
    timeSlot tsDone{};
    int idService;

public:
    Request(int idRequest, int idCluster, timeSlot tsGenerate, timeSlot tsDeadline, timeSlot tsDone, int idService);

    int getIdRequest() const;

    void setIdRequest(int idRequest);

    void setTsDone(int tsDone);

    int getIdCluster() const;

    timeSlot getTsGenerate() const;

    timeSlot getTsDeadline() const;

    timeSlot getTsDone() const;

    int getIdService() const;

    void showRequests(std::vector<Request> requests);

};


#endif //IOTSECURITY_REQUEST_H
