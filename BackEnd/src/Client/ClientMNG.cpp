#include "ClientMNG.hpp"

ClientMNG::ClientMNG(ClientDAO& cDAO)
: m_clientDAO{cDAO}
{}

bool ClientMNG::createClient(const std::string& name, const std::string& phoneNumber, 
                             const std::string& address, const double bill){

    m_clientDAO.createClient(name, phoneNumber, address, bill);
    return true;
}

bool ClientMNG::deleteClient(const int id){
    m_clientDAO.deleteClient(id);
    return true;
}

std::vector<Client> ClientMNG::retrieveClientByName(const std::string& name){
    return m_clientDAO.retrieveClientByName(name);
}

std::vector<Client> ClientMNG::retrieveAllClient(){
    return m_clientDAO.listAllClient();
}

Client ClientMNG::retrieveClient(const int id){
    return m_clientDAO.retrieveClient(id);
}


bool ClientMNG::updateClient(const int id, const std::string& name, 
                             const std::string& phoneNumber, const std::string& 
                             address, const double bill){
    m_clientDAO.updateClient(id, name, phoneNumber, address, bill);
    return true;
}


