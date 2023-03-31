#ifndef IOTSECURITY_REQUEST_H
#define IOTSECURITY_REQUEST_H

#include <iostream>
#include <vector>

typedef int timeSlot;

class Request {

    int id;
    timeSlot tsGenerate;
    timeSlot tsDeadline;
    timeSlot tsDone;

public:
    Request(int id, timeSlot tsGenerate, timeSlot tsDeadline, timeSlot tsDone);

    void setTsDone(float tsDone);

    int getId() const;

    timeSlot getTsGenerate() const;

    timeSlot getTsDeadline() const;

    timeSlot getTsDone() const;

    std::vector<Request> generatorRequests();

    void addRequest(std::vector<Request> requests, Request newRequest);

    void oldRequest(std::vector<Request> oldRequests, Request currentRequest);
};


#endif //IOTSECURITY_REQUEST_H
