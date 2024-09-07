#include "ProductOrderDAO.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <iostream>

ProductOrderDAO::ProductOrderDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{}

bool ProductOrderDAO::createProductOrder(const int sellOrder, const int product, const int quantity, const double discount, const double price){
   try{
      m_theos.prepareStatement("insert into productOrder (sellOrder, product, quantity, discount, price) values (?,?,?,?,?,?)");  
      m_theos.getStatement()->setInt(1, sellOrder);
      m_theos.getStatement()->setInt(2, product);
      m_theos.getStatement()->setInt(3, quantity);
      m_theos.getStatement()->setDouble(4, discount);
      m_theos.getStatement()->setDouble(5, price);
      m_theos.query(CREATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

bool ProductOrderDAO::deleteProductOrder(const int sellOrder){
   try{
      m_theos.prepareStatement("delete from productOrder where sellOrder = ?");  
      m_theos.getStatement()->setInt(1, sellOrder);
      m_theos.query(DELETE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

bool ProductOrderDAO::updateProductOrder(const int sellOrder, const int product, const int quantity, const double discount, const double price){
   try{
      m_theos.prepareStatement("update productOrder set product=?, quantity=?, discount=?, price=? where sellOrder = ?");  
      m_theos.getStatement()->setInt(1, product);
      m_theos.getStatement()->setInt(2, quantity);
      m_theos.getStatement()->setDouble(3, discount);
      m_theos.getStatement()->setDouble(4, price);
      m_theos.getStatement()->setInt(5, sellOrder);
      m_theos.query(UPDATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}


std::vector<ProductOrder> ProductOrderDAO::retrieveProductOrderById(const int id){
   try{
      m_theos.prepareStatement("select * from productOrder where sellOrder = ?");  
      m_theos.getStatement()->setInt(1, id);
      m_theos.query(RETRIEVE);

      std::vector<ProductOrder> vec{};
      while(m_theos.getResult()->next()){
         vec.push_back(ProductOrder(m_theos.getResult()->getInt("sellOrder"),
                                    m_theos.getResult()->getInt("product"), 
                                    m_theos.getResult()->getInt("quantity"), 
                                    m_theos.getResult()->getDouble("discount"),
                                    m_theos.getResult()->getDouble("price")));
      }

      return vec;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

}

