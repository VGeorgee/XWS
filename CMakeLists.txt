cmake_minimum_required(VERSION 3.15)
project(webserver C)
link_libraries(ws2_32 wsock32)
set(CMAKE_C_STANDARD 11)

add_executable(webserver src/main.c src/driver.c src/routes.c)