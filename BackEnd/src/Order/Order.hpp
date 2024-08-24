#ifndef ORDER_2210
#define ORDER_2210

#include "../Client/Client.hpp"
#include "../Product/Product.hpp"
#include <array>
#include <chrono>
#include <vector>

using year_month_day = std::chrono::year_month_day;
class sellOrder{

public:
    sellOrder(int id, int clientId, int sellerId, int deliveredBy, int status, int paymentMethod, std::string date, double price);
   ~sellOrder(){}

   // Setters
   bool setId(int id);
   bool setClient(int id);
   bool setSeller(int id);
   bool setDeliveredBy(int id);

   bool setPrice(double price);
   bool setDate(std::string date);

   // Getters
   int            getId();
   Client&        getBuyer();
   double         getPrice();
   const year_month_day getDate();

private:
   int               m_id{};
   int	             m_clientId;
   int               m_sellerId;
   int               m_deliveredBy;
   int               m_status;
   int               m_paymentMethod;
   std::string       m_date{};
   double	     m_price{};
};

#endif
