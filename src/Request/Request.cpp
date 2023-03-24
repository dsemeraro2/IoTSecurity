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

void Request::generatorRequest() {

}

//Add request in queue
void Request::addRequest() {

}

//Add done request in a queue
void Request::oldRequest() {

}
