cmake_minimum_required(VERSION 3.28)
project(RemoveTool)

add_executable(${PROJECT_NAME} main.c)
target_include_directories(${PROJECT_NAME} PRIVATE "./")
