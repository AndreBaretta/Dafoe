#ifndef PRODUCTORDERDAO_2343
#define PRODUCTORDERDAO_2343
#include "../DafoeGod/DafoeGod.hpp"
#include "ProductOrder.hpp"

class ProductOrderDAO{
public:
   ProductOrderDAO(DafoeGod& dafoe);
   bool createProductOrder(const int sellOrder, const int product, const int quantity, const double discount, const double price);
   bool deleteProductOrder(const int sellOrder, const int product);
   bool updateProductOrder(const int sellOrder, const int product, const int quantity, const double discount, const double price);
   std::vector<ProductOrder> retrieveAllProductOrder(const int sellOrderId);

private:
   DafoeGod& m_theos;
};

#endif
