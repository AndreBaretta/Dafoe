#include "CategoryMNG.hpp"

CategoryMNG::CategoryMNG(CategoryDAO& categoryDAO, JsonBuilder& jsonBuilder)
: m_categoryDAO{categoryDAO}
, m_jsonBuilder{jsonBuilder}
{}

json CategoryMNG::retrieveAllCategories(){
   try{
      std::vector<Category> categories = this->m_categoryDAO.listCategories();
      json json = this->m_jsonBuilder.categoryVectorToJson(categories);
      return json;
   }catch(std::exception &e){
      throw;
   }
}

json CategoryMNG::retrieveCategory(const int id){
   try{
      std::vector<Category> category = this->m_categoryDAO.retrieveCategory(id);
      json json = this->m_jsonBuilder.categoryVectorToJson(category);
      return json;
   }catch(std::exception &e){
      throw;
   }
}

bool CategoryMNG::createCategory(const std::string& name){
   bool response = this->m_categoryDAO.createCategory(name);
   return response;
}

bool CategoryMNG::updateCategory(const int id, const std::string& name){
   bool response = this->m_categoryDAO.updateCategory(id,name);
   return response;
}

bool CategoryMNG::deleteCategory(const int id){
   bool response = this->m_categoryDAO.deleteCategory(id);
   return response;
}

