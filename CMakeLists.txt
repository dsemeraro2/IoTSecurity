cmake_minimum_required(VERSION 3.24)
project(IoTSecurity)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(IoTSecurity src/main.cpp src/Satellite/Satellite.cpp src/Satellite/Satellite.h src/Orchestrator/Orchestrator.h src/Cluster/Cluster.cpp src/Cluster/Cluster.h src/Request/Request.cpp src/Request/Request.h src/Service/Service.cpp src/Service/Service.h src/VisibilityMatrix/VisibilityMatrix.cpp src/VisibilityMatrix/VisibilityMatrix.h src/AllocationServicesMatrix/AllocationServicesMatrix.cpp src/AllocationServicesMatrix/AllocationServicesMatrix.h src/Constellation/Constellation.cpp src/Constellation/Constellation.h src/Simulation/Simulation.cpp src/Simulation/Simulation.h src/Solution/Solution.cpp src/Solution/Solution.h src/TabuSearch/TabuSearch.cpp src/TabuSearch/TabuSearch.h)

