#include "Company.hpp"
#include <string>
#include <array>

Company::Company(int id, std::string name, std::string address, std::array<char, 14> cnpj)
: Client(id, name, address)
, m_cnpj(cnpj)
{}

std::array<char, 14>& Company::getCnpj(){return this->m_cnpj;}

