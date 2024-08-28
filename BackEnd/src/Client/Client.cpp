#include "Client.hpp"
#include <string>
#include <string_view>

Client::Client(const int id, const std::string& name, const std::string& phoneNumber=nullptr, const std::string& address=nullptr, const double bill=0)
: m_id{id}
, m_name{name}
, m_phoneNumber{phoneNumber}
, m_address{address}
, m_bill{bill}
{}

bool Client::setBill(double bill) {
    this->m_bill = bill;
    return true;
}

bool Client::setAddress(std::string add){
    this->m_address = add;
    return true;
}

bool Client::setName(std::string name){
    this->m_name = name;
    return true;
}

int Client::getId(){return this->m_id;}
std::string_view Client::getName(){return this->m_name;}
std::string_view Client::getAddress(){return this->m_address;}
double Client::getBill(){return this->m_bill;}


