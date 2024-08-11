#include "Client.hpp"
#include <string>
#include <string_view>


Client::Client(int id, std::string name, std::string address)
: m_id{id}
, m_name{name}
, m_address{address}
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


