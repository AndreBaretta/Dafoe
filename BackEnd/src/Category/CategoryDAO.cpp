#include "CategoryDAO.hpp"
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <memory>

CategoryDAO::CategoryDAO(DafoeGod& dafoe) : m_theos{dafoe}
{}

bool CategoryDAO::createCategory(std::string name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into category (name) values (?)")};
   stmt->setString(1, name);
   stmt->executeQuery();

   return true;
}

bool CategoryDAO::deleteCategory(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("delete from category where id = ?")};
   stmt->setInt(1, id);
   stmt->executeQuery();

   return true;
}

bool CategoryDAO::updateCategory(const int id, std::string name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("update category set name = ? where id = ?")};
   stmt->setInt(1, id);
   stmt->setString(2, name);
   stmt->executeQuery();

   return true;
}

std::vector<Category> CategoryDAO::listCategories(){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from product")};
   sql::ResultSet* result {stmt->executeQuery()};
   std::vector<Category> categories{};

   while(result->next()){
      categories.push_back(Category(result->getInt("id"), static_cast<std::string>(result->getString("name"))));
   }

   return categories;
}
