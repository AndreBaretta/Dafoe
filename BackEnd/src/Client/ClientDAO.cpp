#include "ClientDAO.hpp"
#include <mariadb/conncpp/PreparedStatement.hpp>

ClientDAO::ClientDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{}

bool ClientDAO::createClient(const std::string& name, const std::string& phoneNumber=nullptr,
                             const std::string& address=nullptr, const double bill=0){
    
    std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into client (id, name, phone, address, bill) values (?,?,?,?,?)")};
    stmt->setInt(1, s_id++);
    stmt->setString(2, name);
    stmt->setString(3, phoneNumber);
    stmt->setString(4, address);
    stmt->setDouble(5, bill);
    stmt->executeQuery();

    return true;

}

bool ClientDAO::deleteClient(const int id){
    
    std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("delete from client where id = ?")};
    stmt->setInt(1, id);
    stmt->executeQuery();

    return true;
}

bool ClientDAO::updateClient(const int id, const std::string& name, const std::string& phoneNumber=nullptr, const std::string& address=nullptr, const double bill=0){
    
    std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("update cliente name = ?, phone = ?, address = ?, bill = ? where id = ?")};

    stmt->setString(1, name);
    stmt->setString(2, phoneNumber);
    stmt->setString(3, address);
    stmt->setDouble(4, bill);
    stmt->setInt(5, id);
    stmt->executeQuery();
    
    return true;
}

std::vector<Client> ClientDAO::retrieveClient(const std::string& name){
    
    std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from client where name like ?")};
    stmt->setString(1, '%'+ name + '%');
    sql::ResultSet* result = stmt->executeQuery();
    
    std::vector<Client> clients{};

    while(result->next()){
        clients.push_back(Client(result->getInt("id"), static_cast<std::string>(result->getString("name")),
                                 static_cast<std::string>(result->getString("phoneNumber")), static_cast<std::string>(result->getString("address")),
                                 result->getDouble("bill")));

    }

    return clients;
}

