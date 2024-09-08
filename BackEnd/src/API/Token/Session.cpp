#include "Session.hpp"

Session::Session(const int id, const bool isAdmin)
: m_id{id}
, m_admin{isAdmin}
{}

int Session::getId(){
   return this->m_id;
}

bool Session::getAdmin(){
   return this->m_admin;
}



