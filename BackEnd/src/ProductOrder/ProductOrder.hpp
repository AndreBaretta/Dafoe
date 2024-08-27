#ifndef PRODUCTORDER_2332
#define PRODUCTORDER_2332

class ProductOrder{
public:
   ProductOrder(int sellOrder, int product, int quantity, double discount, double price);
private:
   int m_SellOrder{};
   int m_product{};
   int m_quantity{};
   double m_discount{};
   double m_price{};
};

#endif
