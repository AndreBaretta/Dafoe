# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name
project(Dafoe)

# Set the C++ standard (optional)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CERT_PATH "${CMAKE_SOURCE_DIR}/BackEnd/src/API/Server/cert.pem")
set(KEY_PATH "${CMAKE_SOURCE_DIR}/BackEnd/src/API/Server/key.pem")
add_definitions(-DCERT_PATH="${CERT_PATH}")
add_definitions(-DKEY_PATH="${KEY_PATH}")

set(SOURCES
   BackEnd/src/API/Server/Server.cpp
   BackEnd/src/API/Json/JsonBuilder.cpp
   BackEnd/src/DafoeGod/DafoeGod.cpp
   # HTTP
   BackEnd/src/API/HTTPRequestHandler/HTTPRequestHandler.cpp
   BackEnd/src/API/HTTPRequestParser/HTTPRequestParser.cpp
   BackEnd/src/API/HTTPRequest/HTTPRequest.cpp 
   BackEnd/src/API/HTTPResponseBuilder/HTTPResponseBuilder.cpp
   BackEnd/src/API/HTTPResponse/HTTPResponse.cpp
   # Product
   BackEnd/src/Product/Product.cpp
   BackEnd/src/Product/ProductDAO.cpp
   BackEnd/src/Product/ProductMNG.cpp
   # Category
   BackEnd/src/Category/Category.cpp
   BackEnd/src/Category/CategoryDAO.cpp
   BackEnd/src/Category/CategoryMNG.cpp
   # PaymentMethod
   BackEnd/src/PaymentMethod/PaymentMethod.cpp
   BackEnd/src/PaymentMethod/PaymentMethodDAO.cpp
   BackEnd/src/PaymentMethod/PaymentMethodMNG.cpp
   # Client
   BackEnd/src/Client/Client.cpp
   BackEnd/src/Client/ClientDAO.cpp
   BackEnd/src/Client/ClientMNG.cpp
   # Employee
   BackEnd/src/Employee/Employee.cpp
   BackEnd/src/Employee/EmployeeDAO.cpp
   BackEnd/src/Employee/EmployeeMNG.cpp
   # Manufacturer
   BackEnd/src/Manufacturer/Manufacturer.cpp
   BackEnd/src/Manufacturer/ManufacturerDAO.cpp
   BackEnd/src/Manufacturer/ManufacturerMNG.cpp
   # SellOrder
   BackEnd/src/SellOrder/SellOrder.cpp
   BackEnd/src/SellOrder/SellOrderDAO.cpp
   BackEnd/src/SellOrder/SellOrderMNG.cpp
   # Status
   BackEnd/src/Status/Status.cpp
   BackEnd/src/Status/StatusDAO.cpp
   BackEnd/src/Status/StatusMNG.cpp
   # GenericProduct
   BackEnd/src/GenericProduct/GenericProduct.cpp
   BackEnd/src/GenericProduct/GenericProductDAO.cpp
   BackEnd/src/GenericProduct/GenericProductMNG.cpp
   # ProductOrder
   BackEnd/src/ProductOrder/ProductOrder.cpp
   BackEnd/src/ProductOrder/ProductOrderDAO.cpp
   # User
   BackEnd/src/User/User.cpp
   BackEnd/src/User/UserDAO.cpp
   BackEnd/src/User/UserMNG.cpp
   # JWT
   BackEnd/src/API/Token/JWToken.cpp
   BackEnd/src/API/Token/Session.cpp
   # Teste
   BackEnd/src/API/teste.cpp
   BackEnd/src/Test/Test.cpp
   )
# Add an executable target
add_executable(teste.out ${SOURCES})
target_link_libraries(teste.out mariadbcpp ssl crypto)

