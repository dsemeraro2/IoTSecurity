#ifndef IOTSECURITY_REQUEST_H
#define IOTSECURITY_REQUEST_H

typedef float timeSlot;

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

    void generatorRequest();

    void addRequest();

    void oldRequest();
};


#endif //IOTSECURITY_REQUEST_H
