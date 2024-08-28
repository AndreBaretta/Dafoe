#ifndef ORDER_2210
#define ORDER_2210

#include <string>

class SellOrder{

public:
    SellOrder(int id, int clientId, int sellerId, int deliveredBy, int status, int paymentMethod, std::string date, double price);
   ~SellOrder(){}

   // Setters
   bool setId(int id);
   bool setClient(int id);
   bool setSeller(int id);
   bool setDeliveredBy(int id);

   bool setPrice(double price);
   bool setDate(std::string date);

   // Getters
   int            getId();
   int       getBuyer();
   double         getPrice();
   std::string& getDate();

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
