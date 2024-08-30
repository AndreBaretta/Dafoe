#include "ProductOrder.hpp"

ProductOrder::ProductOrder(int sellOrder, int product, int quantity, double discount, double price)
: m_SellOrder{sellOrder}
, m_product{product}
, m_quantity{quantity}
, m_discount{discount}
, m_price{price}
{}
