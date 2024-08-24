#ifndef DAFOEGOD_2013
#define DAFOEGOD_2013

#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <mariadb/conncpp/SQLString.hpp>
#include <mariadb/conncpp/Statement.hpp>
#include <mariadb/conncpp/jdbccompat.hpp>

class ProductDAO;
class ClientDAO;
class OrderDAO;
class CategoryDAO;
class EmployeeDAO;
class ManufacturerDAO;

class DafoeGod{
public:
    DafoeGod();
    ~DafoeGod();
    sql::ResultSet* query(const std::string& queryArgument);
    private:
    sql::Driver* driver{};
    sql::SQLString url{};
    sql::Properties properties{};
    sql::Connection* conn{};
    sql::Statement* statement{};
    sql::ResultSet* res{};
    friend class ProductDAO;
    friend class ClientDAO;
    friend class OrderDAO;
    friend class CategoryDAO;
    friend class EmployeeDAO;
    friend class ManufacturerDAO;
};

#endif
