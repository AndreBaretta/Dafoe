#include <array>
#include "Person.hpp"

Person::Person(int id, std::string name, std::string address, std::array<char, 11> cpf)
: Client(id, name, address)
, m_cpf(cpf)
{}

std::array<char, 11>& Person::getCpf(){return this->m_cpf;}

