cmake_minimum_required(VERSION 3.4)
project(HttpServer)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        src/HTTP_Server/main.c
        src/HTTP_Server/http_server.h)

add_executable(HttpServer ${SOURCE_FILES})
