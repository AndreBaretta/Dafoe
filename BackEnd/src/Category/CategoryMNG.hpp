
#ifndef CATEGORYMNG_0107
#define CATEGORYMNG_0107
#include "CategoryDAO.hpp"
#include "Category.hpp"
#include "../API/Json/JsonBuilder.hpp"
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class CategoryMNG{
   public:
      CategoryMNG(CategoryDAO& categoryDAO, JsonBuilder& jsonBuilder);
      json retrieveAllCategories();
      json retrieveCategory(const int id);
      bool createCategory(const std::string& name);
      bool deleteCategory(const int id);
      bool updateCategory(const int id, const std::string& name);

   private:
      CategoryDAO& m_categoryDAO;
      JsonBuilder& m_jsonBuilder;

};

#endif
