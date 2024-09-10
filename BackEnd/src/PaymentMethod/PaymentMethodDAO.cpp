#include "PaymentMethodDAO.hpp"
#include "PaymentMethod.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <vector>
#include <iostream>

PaymentMethodDAO::PaymentMethodDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{}

bool PaymentMethodDAO::createPaymentMethod(const std::string& name){
   try{
      m_theos.prepareStatement("insert into paymentMethod (name) values (?)");
      m_theos.getStatement()->setString(1, name);
      m_theos.query(CREATE);

      return true;

   }catch(std::exception& e){
      std::cout << e.what() << '\n';
      return false;
   }
}

bool PaymentMethodDAO::deletePaymentMethod(const int id){
   try{
      m_theos.prepareStatement("delete from paymentMethod where id = ?");
      m_theos.getStatement()->setInt(1, id);
      m_theos.query(DELETE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool PaymentMethodDAO::updatePaymentMethod(const int id, const std::string& name){
   try{
      m_theos.prepareStatement("update paymentMethod set name = ? where id = ?");
      m_theos.getStatement()->setString(1, name);
      m_theos.getStatement()->setInt(2, id);
      m_theos.query(UPDATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

std::vector<PaymentMethod> PaymentMethodDAO::listPayment(){
   try{
      m_theos.prepareStatement("select * from paymentMethod");
      m_theos.query(RETRIEVE);

      std::vector<PaymentMethod> vec{};

      while(m_theos.getResult()->next()){
         vec.push_back(PaymentMethod(m_theos.getResult()->getInt("id"),
                                     m_theos.getResult()->getString("name").c_str()));
      }

      return vec;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

}

std::vector<PaymentMethod> PaymentMethodDAO::retrievePaymentMethod(const int id){
   try{
      m_theos.prepareStatement("select * from paymentMethod where id = ?");
      m_theos.getStatement()->setInt(1, id);
      m_theos.query(RETRIEVE);

      std::vector<PaymentMethod> pMethod{};

      if(!m_theos.getResult()->next())
         return pMethod;

      pMethod.push_back(PaymentMethod(m_theos.getResult()->getInt("id"), m_theos.getResult()->getString("name").c_str()));

      return pMethod;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

}

