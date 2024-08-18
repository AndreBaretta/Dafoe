#include "Manufacturer.hpp"

Manufacturer::Manufacturer(int id, std::string name)
: m_id{id}
, m_name{name}
{}

Manufacturer::Manufacturer(int id)
: m_id{id}
, m_name{"template"}
{}

int Manufacturer::getId(){return this->m_id;}
