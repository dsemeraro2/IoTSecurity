cmake_minimum_required(VERSION 3.24)
project(IoTSecurity)

set(CMAKE_CXX_STANDARD 17)

add_executable(IoTSecurity src/main.cpp src/Satellite/Satellite.cpp src/Satellite/Satellite.h src/Orchestrator/Orchestrator.h src/Cluster/Cluster.cpp src/Cluster/Cluster.h src/Request/Request.cpp src/Request/Request.h src/Service/Service.cpp src/Service/Service.h)
