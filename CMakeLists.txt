# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name
project(Dafoe)

# Set the C++ standard (optional)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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
   BackEnd/src/PaymentMethod/PaymentMethod.cpp
   BackEnd/src/PaymentMethod/PaymentMethodMNG.cpp
   BackEnd/src/PaymentMethod/PaymentMethodDAO.cpp
   BackEnd/src/Employee/Employee.cpp
   BackEnd/src/Manufacturer/Manufacturer.cpp
   BackEnd/src/Category/Category.cpp
   BackEnd/src/Category/CategoryDAO.cpp
   BackEnd/src/Category/CategoryMNG.cpp
   BackEnd/src/Test/Test.cpp
   )
# Add an executable target
add_executable(teste.out ${SOURCES})
target_link_libraries(teste.out mariadbcpp)

