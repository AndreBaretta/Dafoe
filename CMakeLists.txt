# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name
project(Dafoe)

# Set the C++ standard (optional)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# List of source files
set(SOURCES
   BackEnd/src/API/teste.cpp
   BackEnd/src/API/HTTPRequest/HTTPRequest.cpp 
   BackEnd/src/API/HTTPRequestHandler/HTTPRequestHandler.cpp
   BackEnd/src/API/HTTPRequestParser/HTTPRequestParser.cpp
   BackEnd/src/API/HTTPResponse/HTTPResponse.cpp
   BackEnd/src/API/HTTPResponseBuilder/HTTPResponseBuilder.cpp
   BackEnd/src/API/TCPServer/TCPServer.cpp
   BackEnd/src/API/Json/JsonBuilder.cpp
   BackEnd/src/DafoeGod/DafoeGod.cpp
   BackEnd/src/Product/ProductDAO.cpp
   BackEnd/src/Product/ProductMNG.cpp
   BackEnd/src/Product/Product.cpp
   )
#find mariadb connector

find_module(mariadb-conncpp REQUIRED)

# Add an executable target
add_executable(teste.out ${SOURCES})

#include directories for mariadb
target_include_directories(teste.out PRIVATE ${CMAKE_SOURCE_DIR}/external/json/include)
#link mariadb library

target_link_libraries(teste.out mariadb::conncpp)

