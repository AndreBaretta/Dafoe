#include "ClientMNG.hpp"

ClientMNG::ClientMNG(ClientDAO& cDAO)
: m_cDAO{cDAO}
{}

bool ClientMNG::createClient(const std::string& name, const std::string& phoneNumber, 
                             const std::string& address, const double bill){

    m_cDAO.createClient(name, phoneNumber, address, bill);
    return true;
}

bool ClientMNG::deleteClient(const int id){
    m_cDAO.deleteClient(id);
    return true;
}

std::vector<Client> ClientMNG::retrieveClient(const std::string& name){
    return m_cDAO.retrieveClient(name);
}

bool ClientMNG::updateClient(const int id, const std::string& name, 
                             const std::string& phoneNumber, const std::string& 
                             address, const double bill){
    m_cDAO.updateClient(id, name, phoneNumber, address, bill);
    return true;
}
