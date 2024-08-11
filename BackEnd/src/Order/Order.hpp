#ifndef ORDER_2210
#define ORDER_2210

#include "../Client/Client.hpp"
#include "../Product/Product.hpp"
#include <array>
#include <chrono>

class Order{
   public:
      explicit Order(int id, Client* buyer, double price, year_month_day date){}
      ~Order(){}
      
      // Setters
      bool setId(int);
      bool setBuyer(Client*);
      bool setPrice(double);
      bool setDate(year_month_day);

      // Getters
      int            getId();
      Client*        getBuyer();
      double         getPrice();
      year_month_day getDate();
	    
   private:
      int            m_id{};
      Client* 	     m_buyer{};
      double	     m_price{};
      year_month_day m_date{};
};

#endif
