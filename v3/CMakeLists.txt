cmake_minimum_required(VERSION 3.16)
project(calculator)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_PREFIX_PATH "/usr/local" )
find_package(Drogon REQUIRED)

add_executable(calculator main.cpp controllers/Controller.cpp)
target_link_libraries(calculator PRIVATE ${DROGON_LIBRARIES})
