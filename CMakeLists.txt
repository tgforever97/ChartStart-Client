cmake_minimum_required(VERSION 3.15)
project(ChartStart_Client)

set(CMAKE_CXX_STANDARD 14)

add_executable(ChartStart_Client main.cpp include/Client.h include/Common.h Client.cpp include/Utils.h utils.cpp)