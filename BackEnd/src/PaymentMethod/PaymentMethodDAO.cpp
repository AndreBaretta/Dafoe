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

bool PaymentMethodDAO::createPaymentMethodDAO(const std::string& name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into manufacturer (id, name) values (?,?)")};
   stmt->setInt(1, s_id++);
   stmt->setString(2, name);
   stmt->executeQuery();

   return true;
}

bool PaymentMethodDAO::deletePaymentMethodDAO(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("delete from manufacturer where id = ?")};
   stmt->setInt(1, id);
   stmt->executeQuery();

   return true;
}

bool PaymentMethodDAO::updatePaymentMethodDAO(const int id, const std::string& name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("update manufacturer set name = ? where id = ?")};

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
