cmake_minimum_required(VERSION 3.0)

project(Potter)

find_package(Threads REQUIRED)

add_executable(potter open_file.c ../ProxyLab/proxylab-handout/csapp.c)

target_link_libraries(potter PRIVATE Threads::Threads)

