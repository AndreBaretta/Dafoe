#include "ProductDAO.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
//NEED TO ADD TRY CATCHES TO ALL SQL QUERIES


ProductDAO::ProductDAO(DafoeGod& zeus)
: m_theos{zeus}
{}

std::vector<Product> ProductDAO::retrieveByName(std::string name){
    std::unique_ptr<sql::PreparedStatement> state{m_theos.conn->prepareStatement("select * from product where name like ?")};
    state->setString(1, '%' + name + '%');
    sql::ResultSet* result {state->executeQuery()};

    Product product{};
    std::vector<Product> products{};
    while(result->next()){
        std::string name = result->getString("name").c_str();
        std::string barcode = result->getString("barcode").c_str();
        std::string reference = result->getString("reference").c_str();
        product = Product(result->getInt("id"), name, barcode, result->getDouble("price"),
                          result->getDouble("cost"), reference, result->getInt("quantity"));
        products.push_back(product);
    }

    return products;
}

Product ProductDAO::retrieveByID(const int id){
    std::unique_ptr<sql::PreparedStatement> state{m_theos.conn->prepareStatement("select * from product where id = ?")};
    state->setInt(1,id);
    sql::ResultSet* result {state->executeQuery()};
    result->next();
    std::string name = result->getString("name").c_str();
    std::string barcode = result->getString("barcode").c_str();
    std::string reference = result->getString("reference").c_str();
    Product product = Product(result->getInt("id"), name, barcode, result->getDouble("price"),
                      result->getDouble("cost"), reference, result->getInt("quantity"));

    return product;
}

Product ProductDAO::retrieveByBarCode(std::string barCode){
    std::unique_ptr<sql::PreparedStatement> state{m_theos.conn->prepareStatement("select * from product where barcode = ?")};
    state->setString(1,barCode);
    sql::ResultSet* result {state->executeQuery()};
    
    std::string name = result->getString("name").c_str();
    std::string barcode = result->getString("barcode").c_str();
    std::string referenceStr = result->getString("reference").c_str();
    Product product = Product(result->getInt("id"), name, barcode, result->getDouble("price"),
                      result->getDouble("cost"), referenceStr, result->getInt("quantity"));

    return product;
}

std::vector<Product> ProductDAO::retrieveByReference(std::string reference){
    std::unique_ptr<sql::PreparedStatement> state{m_theos.conn->prepareStatement("select * from product where reference like ?")};
    state->setString(1,'%' + reference + '%');
    sql::ResultSet* result {state->executeQuery()};
    
    Product product{};
    std::vector<Product> products{};
    while(result->next()){
        std::string name = result->getString("name").c_str();
        std::string barcode = result->getString("barcode").c_str();
        std::string reference = result->getString("reference").c_str();
        product = Product(result->getInt("id"), name, barcode, result->getDouble("price"),
                          result->getDouble("cost"), reference, result->getInt("quantity"));
        products.push_back(product);
    }

    return products;
}
std::vector<Product> ProductDAO::retrieveByManufacturer(std::string manufacturer){
    std::unique_ptr<sql::PreparedStatement> state{m_theos.conn->prepareStatement("select id from manufacturer where name like ?")};
    state->setString(1,'%' + manufacturer + '%');
    sql::ResultSet* result {state->executeQuery()};

    std::unique_ptr<sql::PreparedStatement> statement{m_theos.conn->prepareStatement("select genericProduct from product where manufacturer =")};
    statement->setInt(1, result->getInt("id"));
    result = statement->executeQuery();

    Product product;
    std::vector<Product> products{};
    while(result->next()){
        std::string name = result->getString("name").c_str();
        std::string barcode = result->getString("barcode").c_str();
        std::string reference = result->getString("reference").c_str();
        product = Product(result->getInt("id"), name, barcode, result->getDouble("price"),
                          result->getDouble("cost"), reference, result->getInt("quantity"));
        products.push_back(product);
    }

    return products;
}

bool ProductDAO::createProduct(const std::string& name, const int manufacturerId, const int quantity, 
                               const int category, const std::string& barCode, const std::string& reference,
                               const double cost, const double price){

    std::unique_ptr<sql::PreparedStatement> state{m_theos.conn->prepareStatement("insert into genericProduct (id,name,quantity,category) values (?,?,?,?)")};
    state->setInt(1, this->s_id);
    state->setString(2, name);
    state->setInt(3, quantity);
    state->setInt(4, category);
    state->executeQuery();

    std::unique_ptr<sql::PreparedStatement> statement{m_theos.conn->prepareStatement("insert into product (id, genericProduct, manufacturer, barcode, price, cost, reference, quantity) values (?, ?, ?, ?, ?, ?, ?)")};
    statement->setInt(1, this->s_id++);
    statement->setInt(2, this->s_genericProductId++);
    statement->setInt(3, manufacturerId);
    statement->setString(4, barCode);
    statement->setDouble(5, price);
    statement->setDouble(6, cost);
    statement->setString(7, reference);
    statement->setInt(8, quantity);

    statement->executeQuery();

    return true;
}

bool ProductDAO::deleteProduct(const int id){
    std::unique_ptr<sql::PreparedStatement> state(m_theos.conn->prepareStatement("delete from genericProduct where id = ?"));
    state->setInt(1, id);
    state->executeQuery();


    std::unique_ptr<sql::PreparedStatement> statement(m_theos.conn->prepareStatement("delete from product where genericProduct = ?"));
    statement->setInt(2, id);
    statement->executeQuery();

    return true;
}

bool ProductDAO::updateProduct(const int id, const std::string& name, const int manufacturerId, 
                               const int quantity, const int category, const std::string& barCode, 
                               const std::string& reference, const double cost, const double price){
        
    std::unique_ptr<sql::PreparedStatement> state(m_theos.conn->prepareStatement("update product set name = ?, quantity = ?, category = ? where id = ?"));
    state->setString(1, name);
    state->setInt(2, quantity);
    state->setInt(3, category);
    state->setInt(4, id);
    state->executeQuery();

    std::unique_ptr<sql::PreparedStatement> statement(m_theos.conn->prepareStatement("update productManufacturer set manufacturer = ?, barcode = ?, price = ?, cost = ?, reference = ?, quantity = ? where product = ?"));
    statement->setInt(1, manufacturerId);
    statement->setString(2, barCode);
    statement->setDouble(3, price);
    statement->setDouble(4, cost);
    statement->setString(5, reference);
    statement->setInt(6, quantity);
    statement->setInt(7, id);

    return true;
}

bool ProductDAO::updateCategoryPriceByNumber(const int category, const double price){
    std::unique_ptr<sql::PreparedStatement> state(m_theos.conn->prepareStatement("update productManufacturer set price = price+? where category = ?"));
    state->setDouble(1, price);
    state->setInt(2, category);
    state->executeQuery();

    return true;
}

bool ProductDAO::updateCategoryPriceByPercentage(const int category, const double percentage){
    std::unique_ptr<sql::PreparedStatement> state(m_theos.conn->prepareStatement("update productManufacturer set price = price+(price/100)*? where category = ?"));
    state->setDouble(1, percentage);
    state->setInt(2, category);
    state->executeQuery();

    return true;
}




























