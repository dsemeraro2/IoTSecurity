#ifndef IOTSECURITY_TABUSEARCH_H
#define IOTSECURITY_TABUSEARCH_H

#include "../Solution/Solution.h"
#include "../Request/Request.h"

class TabuSearch {
public:
    TabuSearch();
    void swapMove(Solution *solution, int timeSlotSize, int satellitesSize, int servicesSize);
    void optimizationTabuSearch(std::vector<Request> requests, int timeSlotInitial, int timeSlotTotali);
};


#endif //IOTSECURITY_TABUSEARCH_H
