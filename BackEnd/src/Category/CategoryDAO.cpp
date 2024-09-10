#include "CategoryDAO.hpp"
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <string>
#include <iostream>

CategoryDAO::CategoryDAO(DafoeGod& dafoe) : m_theos{dafoe}
{}

bool CategoryDAO::createCategory(std::string name){
   try{
      m_theos.prepareStatement("insert into category (name) values (?)");
      m_theos.getStatement()->setString(1, name);
      m_theos.query(CREATE);
      return true;
   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool CategoryDAO::deleteCategory(const int id){
   try{
      m_theos.prepareStatement("delete from category where id = ?");
      m_theos.getStatement()->setInt(1, id);
      m_theos.query(DELETE);
      return true;
   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool CategoryDAO::updateCategory(const int id, std::string name){
   try{
      m_theos.prepareStatement("update category set name = ? where id = ?");
      m_theos.getStatement()->setString(1, name);
      m_theos.getStatement()->setInt(2, id);
      m_theos.query(UPDATE); 
      return true;
   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

std::vector<Category> CategoryDAO::listCategories(){
   try{
      m_theos.prepareStatement("select * from category");
      m_theos.query(RETRIEVE);

      std::vector<Category> categories{};

      while(m_theos.getResult()->next()){
         categories.push_back(Category(m_theos.getResult()->getInt("id"), 
                                       m_theos.getResult()->getString("name").c_str()));
      }

      return categories;
   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<Category> CategoryDAO::retrieveCategory(const int id){
   try{
      m_theos.prepareStatement("select * from category where id = ?");
      m_theos.getStatement()->setInt(1,id);
      m_theos.query(RETRIEVE);

      std::vector<Category> category{};
      if(!m_theos.getResult()->next()){
         return category;
      }

      int categoryId = m_theos.getResult()->getInt("id");
      std::string categoryName = m_theos.getResult()->getString("name").c_str();
      category.push_back(Category(categoryId, categoryName));

      return category;
   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}
