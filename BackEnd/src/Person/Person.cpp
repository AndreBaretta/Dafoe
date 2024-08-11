#include <array>
#include "Person.hpp"

Person::Person(std::string name, std::array<char, 11> cpf)
: Client(name)
, m_cpf(cpf)
{}

std::array<char, 11>& Person::getCpf(){return this->m_cpf;}

