#ifndef IOTSECURITY_TABUSEARCH_H
#define IOTSECURITY_TABUSEARCH_H

#include "../Solution/Solution.h"
#include "../Request/Request.h"
#include "../VisibilityMatrix/VisibilityMatrix.h"

class TabuSearch {
public:
    int timeSlot;
    int satellites;
    std::vector<Service> services;
    std::vector<Request> requests;
    Solution solution;
    VisibilityMatrix visibilityMatrix;

    TabuSearch(int timeSlot, int satellites, std::vector<Service> services, const std::vector<Request> &requests,
               const Solution &solution, const VisibilityMatrix &visibilityMatrix);

    void optimizationTabuSearch(int timeSlotInitial, int timeSlotTotali);

    void swapMove(Service service, int sourceTimeSlot, int sourceService, int sourceSatellite, int destTimeSlot,
                  int destService, int destSatellite);

    void tabuSearchIterate(std::vector<Request> tempRequests);
};


#endif //IOTSECURITY_TABUSEARCH_H
