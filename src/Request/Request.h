#ifndef IOTSECURITY_REQUEST_H
#define IOTSECURITY_REQUEST_H

#include <iostream>
#include <vector>
#include "../Service/Service.h"

typedef int timeSlot;

class Request {

    int id{};
    timeSlot tsGenerate{};
    timeSlot tsDeadline{};
    timeSlot tsDone{};
    int idService;

public:
    Request(int id, timeSlot tsGenerate, timeSlot tsDeadline, timeSlot tsDone, int idService);

    void setTsDone(float tsDone);

    int getId() const;

    timeSlot getTsGenerate() const;

    timeSlot getTsDeadline() const;

    timeSlot getTsDone() const;

    void showRequests(std::vector<Request> requests);
};


#endif //IOTSECURITY_REQUEST_H
