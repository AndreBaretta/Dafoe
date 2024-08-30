#include "CategoryMNG.hpp"
#include "Category.hpp"
#include "CategoryDAO.hpp"

CategoryMNG::CategoryMNG(CategoryDAO& cDAO)
: m_cDAO{cDAO}
{}

bool CategoryMNG::createCategory(const std::string& name){
   m_cDAO.createCategory(name);
   return true;
}

bool CategoryMNG::deleteCatagory(const int id){
   m_cDAO.deleteCategory(id);
   return true;
}

bool CategoryMNG::updateCategory(const int id, const std::string& name){
   m_cDAO.updateCategory(id, name);
   return true;
}

std::vector<Category> CategoryMNG::listAllCategories(){
   return m_cDAO.listCategories();
}

Category CategoryMNG::retrieveCategory(const int id){
   return m_cDAO.retrieveCategory(id);
}
