#include "Company.hpp"
#include <string>
#include <array>

Company::Company(std::string name, std::array<char, 14> cnpj)
: Client(name)
, m_cnpj(cnpj)
{}

std::array<char, 14>& Company::getCnpj(){return this->m_cnpj;}

