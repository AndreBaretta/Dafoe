#ifndef CATEGORYMNG_0126
#define CATEGORYMNG_0126
#include "CategoryDAO.hpp"

class CategoryMNG{
public:
    CategoryMNG(CategoryDAO& cDAO);
    bool createCategory(const std::string& name);
    bool deleteCatagory(const int id);
    bool updateCategory(const int id, const std::string& name);
    std::vector<Category> listAllCategories();
    Category retrieveCategory(const int id);

private:
    CategoryDAO& m_cDAO;

};

#endif
