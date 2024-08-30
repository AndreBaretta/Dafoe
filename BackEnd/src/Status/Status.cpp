#include "Status.hpp"

Status::Status(int id, const std::string& name)
: m_id{id}
, m_name{name}
{}

int Status::getId(){return m_id;}
std::string& Status::getName(){return m_name;}
bool Status::setName(const std::string& name){
   m_name = name;
   return true;
}
