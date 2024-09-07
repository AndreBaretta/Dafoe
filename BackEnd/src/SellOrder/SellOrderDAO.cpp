#include <mariadb/conncpp/PreparedStatement.hpp>
#include "SellOrderDAO.hpp"
#include "SellOrder.hpp"
#include <iostream>


SellOrderDAO::SellOrderDAO(DafoeGod& zeus, ProductDAO& pdao)
: m_theos{zeus}
, m_pDAO{pdao}
{}


bool SellOrderDAO::createOrder(const int clientId, const int sellerId,
                               const int deliveredBy, const int status, 
                               const int paymentMethod, const std::string& date, 
                               const double price){
   try{
      m_theos.prepareStatement("insert into sellOrder (client, seller, deliveredBy, status, paymentMethod, date, price) values (?,?,?,?,?,?,?)");
      m_theos.getStatement()->setInt(1, clientId);
      m_theos.getStatement()->setInt(2, sellerId);
      m_theos.getStatement()->setInt(3, deliveredBy);
      m_theos.getStatement()->setInt(4, status);
      m_theos.getStatement()->setInt(5, paymentMethod);
      m_theos.getStatement()->setString(6, date);
      m_theos.getStatement()->setDouble(7, price);
      m_theos.query(CREATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

bool SellOrderDAO::addProductOrder(const int sellOrder, const int product, const int quantity, const double discount, const double price){
  try{
      m_theos.prepareStatement("insert into productOrder (sellOrder, product, quantity, discount, price) values (?,?,?,?,?)");
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

   return false;
}

bool SellOrderDAO::updateProductOrder(const int sellOrder, const int product, const int quantity, const double discount, const double price){
   try{
      m_theos.prepareStatement("update productOrder set quantity=?, discount=?, price=? where sellOrder = ? and product = ?");
      m_theos.getStatement()->setInt(1, quantity);
      m_theos.getStatement()->setDouble(2, discount);
      m_theos.getStatement()->setDouble(3, price);
      m_theos.getStatement()->setInt(4, sellOrder);
      m_theos.getStatement()->setInt(5, product);
      m_theos.query(UPDATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

   return false;
}

bool SellOrderDAO::removeProductOrder(const int sellOrder, const int product){
   try{
      m_theos.prepareStatement("delete from productOrder where sellOrder = ? and producct = ?");
      m_theos.getStatement()->setInt(1, sellOrder);
      m_theos.getStatement()->setInt(2, product);
      m_theos.query(DELETE);

      return true;
      
   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

   return false;
}


bool SellOrderDAO::updateOrder(const int id, const int clientId, const int sellerId,
                               const int deliveredBy, const int status, 
                               const int paymentMethod, const std::string& date, 
                               const double price){
   try{
      m_theos.prepareStatement("update sellOrder set client = ?, seller = ?, deliveredBy = ?, status = ?, paymentMethod = ?, date = ?, price = ? where id = ?");
      m_theos.getStatement()->setInt(1, id);
      m_theos.getStatement()->setInt(2, clientId);
      m_theos.getStatement()->setInt(3, sellerId);
      m_theos.getStatement()->setInt(4, deliveredBy);
      m_theos.getStatement()->setInt(5, status);
      m_theos.getStatement()->setInt(6, paymentMethod);
      m_theos.getStatement()->setString(7, date);
      m_theos.getStatement()->setDouble(8, price);
      m_theos.query(UPDATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<SellOrder> SellOrderDAO::retrieveOrderById(const int id){
   try{
      m_theos.prepareStatement("select * from sellOrder where id = ?");
      m_theos.getStatement()->setInt(1, id);
      m_theos.query(RETRIEVE);

      std::vector<SellOrder> sellOrder{};
      if(!m_theos.getResult()->next())
         return sellOrder;
      sellOrder.push_back(SellOrder(m_theos.getResult()->getInt("id"), m_theos.getResult()->getInt("client"), 
                                    m_theos.getResult()->getInt("seller"), m_theos.getResult()->getInt("deliveredBy"), 
                                    m_theos.getResult()->getInt("status"), m_theos.getResult()->getInt("paymentMethod"), 
                                    m_theos.getResult()->getString("date").c_str(), m_theos.getResult()->getDouble("price")));
      return sellOrder;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<SellOrder> SellOrderDAO::retrieveOrderByClient(const int clientId){
   try{
      m_theos.prepareStatement("select * from sellOrder where client = ?");
      m_theos.getStatement()->setInt(1, clientId);
      m_theos.query(RETRIEVE);

      std::vector<SellOrder> vec{};
      while(m_theos.getResult()->next()){
         vec.push_back(SellOrder(m_theos.getResult()->getInt("id"), m_theos.getResult()->getInt("client"), 
                                 m_theos.getResult()->getInt("seller"), m_theos.getResult()->getInt("delivereBy"), 
                                 m_theos.getResult()->getInt("status"), m_theos.getResult()->getInt("paymentMethod"), 
                                 m_theos.getResult()->getString("date").c_str(), m_theos.getResult()->getDouble("price")));
      }

      return vec;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<SellOrder> SellOrderDAO::retrieveOrderByProduct(const int productId){
   try{
      m_theos.prepareStatement("select * from sellOrder where product = ?");
      m_theos.getStatement()->setInt(1, productId);
      m_theos.query(RETRIEVE);

      std::vector<SellOrder> vec{};
      while(m_theos.getResult()->next()){
         vec.push_back(SellOrder(m_theos.getResult()->getInt("id"), m_theos.getResult()->getInt("client"), 
                                 m_theos.getResult()->getInt("seller"), m_theos.getResult()->getInt("delivereBy"), 
                                 m_theos.getResult()->getInt("status"), m_theos.getResult()->getInt("paymentMethod"), 
                                 m_theos.getResult()->getString("date").c_str(), m_theos.getResult()->getDouble("price")));
      }

      return vec;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<SellOrder> SellOrderDAO::retrieveOrderByStatus(const int statusId){
   try{
      m_theos.prepareStatement("select * from sellOrder where status = ?");
      m_theos.getStatement()->setInt(1, statusId);
      m_theos.query(RETRIEVE);

      std::vector<SellOrder> vec{};
      while(m_theos.getResult()->next()){
         vec.push_back(SellOrder(m_theos.getResult()->getInt("id"), m_theos.getResult()->getInt("client"), 
                                 m_theos.getResult()->getInt("seller"), m_theos.getResult()->getInt("delivereBy"), 
                                 m_theos.getResult()->getInt("status"), m_theos.getResult()->getInt("paymentMethod"), 
                                 m_theos.getResult()->getString("date").c_str(), m_theos.getResult()->getDouble("price")));
      }

      return vec;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<SellOrder> SellOrderDAO::retrieveOrderBySeller(const int sellerId){
   try{
      m_theos.prepareStatement("select * from sellOrder where seller = ?");
      m_theos.getStatement()->setInt(1, sellerId);
      m_theos.query(RETRIEVE);

      std::vector<SellOrder> vec{};
      while(m_theos.getResult()->next()){
         vec.push_back(SellOrder(m_theos.getResult()->getInt("id"), m_theos.getResult()->getInt("client"), 
                                 m_theos.getResult()->getInt("seller"), m_theos.getResult()->getInt("delivereBy"), 
                                 m_theos.getResult()->getInt("status"), m_theos.getResult()->getInt("paymentMethod"), 
                                 m_theos.getResult()->getString("date").c_str(), m_theos.getResult()->getDouble("price")));
      }

      return vec;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<SellOrder> SellOrderDAO::listAllSellOrder(){
   try{
      m_theos.prepareStatement("select * from sellOrder");
      m_theos.query(RETRIEVE);

      std::vector<SellOrder> vec{};
      while(m_theos.getResult()->next()){
         vec.push_back(SellOrder(m_theos.getResult()->getInt("id"), m_theos.getResult()->getInt("client"), 
                                 m_theos.getResult()->getInt("seller"), m_theos.getResult()->getInt("delivereBy"), 
                                 m_theos.getResult()->getInt("status"), m_theos.getResult()->getInt("paymentMethod"), 
                                 m_theos.getResult()->getString("date").c_str(), m_theos.getResult()->getDouble("price")));
      }
      return vec;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

