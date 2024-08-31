#include "User.hpp"

User::User(const int id, const std::string& name, const std::string& password)
: m_id{id}
, m_name{name}
, m_password{password} 
{}

int User::getId() const {
    return m_id;
}

std::string User::getName() const {
    return m_name;
}

std::string User::getPassword() const {
    return m_password;
}

void User::setId(int id) {
    m_id = id;
}

void User::setName(const std::string& name) {
    m_name = name;
}

void User::setPassword(const std::string& password) {
    m_password = password;
}
