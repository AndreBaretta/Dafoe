#include "Order.hpp"

Order::Order(int id, Client* buyer, double price, year_month_day date)
: m_id{id}
, m_buyer{buyer}
, m_price{price}
, m_date{date}
{}

bool Order::setId(int id){
   this->m_id = id;
   return true;
}

bool Order::setBuyer(Client* buyer){
   this->m_buyer = buyer;
   return true;
}

bool Order::setPrice(double price){
   this->m_price = price;
   return true;
}

bool Order::setDate(year_month_date date){
   this->m_date = date;
   return true;
}

int            Order::getId(){return this->m_id;}
Client*        Order::getBuyer(){return this->m_buyer;}
double         Order::getPrice(){return this->m_price;}
year_month_day Order::getDate(){return this->m_date;}

