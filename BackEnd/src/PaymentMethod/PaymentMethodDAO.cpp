#include "PaymentMethodDAO.hpp"
#include "PaymentMethod.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <memory>
#include <vector>

PaymentMethodDAO::PaymentMethodDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{}

bool PaymentMethodDAO::createPaymentMethod(const std::string& name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into paymentMethod (name) values (?)")};
   stmt->setString(1, name);
   stmt->executeQuery();

   return true;
}

bool PaymentMethodDAO::deletePaymentMethod(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("delete from paymentMethod where id = ?")};
   stmt->setInt(1, id);
   stmt->executeQuery();

   return true;
}

bool PaymentMethodDAO::updatePaymentMethod(const int id, const std::string& name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("update paymentMethod set name = ? where id = ?")};

   stmt->setString(1, name);
   stmt->setInt(2, id);
   stmt->executeQuery();

   return true;
}

std::vector<PaymentMethod> PaymentMethodDAO::listPayment(){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from paymentMethod")};
   sql::ResultSet* result{stmt->executeQuery()};
   std::vector<PaymentMethod> vec{};

   while(result->next()){
      vec.push_back(PaymentMethod(result->getInt("id"), static_cast<std::string>(result->getString("name"))));
   }

   return vec;
}

PaymentMethod PaymentMethodDAO::retrievePaymentMethod(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from paymentMethod where id = ?")};
   stmt->setInt(1, id);
   sql::ResultSet* result{stmt->executeQuery()};
   result->next();

   PaymentMethod response = PaymentMethod(result->getInt("id"), static_cast<std::string>(result->getString("name")));
   return response;
}

