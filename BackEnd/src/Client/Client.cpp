#include "Client.hpp"

Client::Client(int id, const std::string& name, const std::string& phoneNumber, const std::string& address, double bill)
: m_id(id)
, m_name(name)
, m_phoneNumber(phoneNumber)
, m_address(address)
, m_bill(bill) 
{}

// Setters
bool Client::setName(const std::string& name) {
    m_name = name;
    return true;
}

bool Client::setAddress(const std::string& address) {
    m_address = address;
    return true;
}

bool Client::setBill(double bill) {
    m_bill = bill;
    return true;
}

// Getters
int Client::getId() const {
    return m_id;
}

std::string_view Client::getName() const {
    return m_name;
}

std::string_view Client::getAddress() const {
    return m_address;
}

double Client::getBill() const {
    return m_bill;
}

