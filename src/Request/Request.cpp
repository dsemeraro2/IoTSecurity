#include "Request.h"

Request::Request(int id, timeSlot tsGenerate, timeSlot tsDeadline, timeSlot tsDone) : id(id), tsGenerate(tsGenerate),
                                                                                      tsDeadline(tsDeadline),
                                                                                      tsDone(tsDone) {}

int Request::getId() const {
    return id;
}

timeSlot Request::getTsGenerate() const {
    return tsGenerate;
}

timeSlot Request::getTsDeadline() const {
    return tsDeadline;
}

timeSlot Request::getTsDone() const {
    return tsDone;
}

void Request::setTsDone(float tsDone) {
    Request::tsDone = tsDone;
}

std::vector<Request> Request::generatorRequests() {

    /*std::vector<Request> requests;

    for (int i = 0; i < 1000; i++) {
        Request::addRequest(requests, {i, 0,1,-1});
    }

    return requests;
*/
}

//Add request in queue
void Request::addRequest(std::vector<Request> requests, Request newRequest) {
    requests.insert(requests.end(), newRequest);
}

//Add done request in a queue
void Request::oldRequest(std::vector<Request> oldRequests, Request currentRequest) {
    oldRequests.insert(oldRequests.end(), currentRequest);
}
