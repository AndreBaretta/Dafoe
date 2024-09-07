#ifndef DAFOEGOD_2013
#define DAFOEGOD_2013
#include <optional>
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <mariadb/conncpp/SQLString.hpp>
#include <mariadb/conncpp/Statement.hpp>
#include <mariadb/conncpp/jdbccompat.hpp>
#include "../Type/Enum.hpp"

class ProductDAO;
class ClientDAO;
class SellOrderDAO;
class CategoryDAO;
class EmployeeDAO;
class ManufacturerDAO;
class StatusDAO;
class PaymentMethodDAO;
class GenericProductDAO;
class ProductOrderDAO;
class UserDAO;

class DafoeGod{
public:
    DafoeGod();
    ~DafoeGod();
    void query(TypeOfTransaction type);
    sql::Connection* getConnection();
    sql::PreparedStatement* getStatement();
    sql::ResultSet* getResult();
    bool prepareStatement(const std::string& stmt);
    private:
    sql::Driver* m_driver{};
    sql::SQLString m_url{};
    sql::Properties m_properties{};
    sql::Connection* m_conn{};
    sql::PreparedStatement* m_statement{};
    sql::ResultSet* m_res{};

    friend class ProductDAO;
    friend class ClientDAO;
    friend class SellOrderDAO;
    friend class CategoryDAO;
    friend class EmployeeDAO;
    friend class ManufacturerDAO;
    friend class StatusDAO;
    friend class PaymentMethodDAO;
    friend class GenericProductDAO;
    friend class ProductOrderDAO;
    friend class UserDAO;
};

#endif
