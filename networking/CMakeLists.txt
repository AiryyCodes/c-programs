cmake_minimum_required(VERSION 3.28)
project(Networking)

add_executable(server server.c)
add_executable(client client.c)
target_include_directories(server PRIVATE "./")
target_include_directories(client PRIVATE "./")
