cmake_minimum_required(VERSION 3.5.1)
project(NLPBeginner)

set(CMAKE_CXX_STANDARD 11)

add_executable(NLPBeginner algorithm/longestCommonSequence.cpp)

#add_executable(NLPBeginner algorithm/start.cpp)




#cmake_minimum_required(VERSION 3.21)
#project(NLPBeginner C)
#
#set(CMAKE_C_STANDARD 11)
#
#include_directories(csapp/ProxyLab/proxylab-handout)
#include_directories(csapp/ProxyLab/proxylab-handout/tiny)
#
##add_executable(NLPBeginner
##        "csapp/Chapter10 SystemIO/bus_dispatching.c"
##)
#add_executable(NLPBeginner
#        "debug_usage/expand_list.c"
#        )
