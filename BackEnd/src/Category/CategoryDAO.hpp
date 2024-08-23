#ifndef CATEGORYDAO_2320
#define CATEGORYDAO_2320

#include "Category.hpp"
#include <vector>
#include "../DafoeGod/DafoeGod.hpp"

class CategoryDAO{
public:
    CategoryDAO(DafoeGod& dafoe);
    bool createCategory(std::string name);
    bool deleteCategory(const int id);
    bool updateCategory(const int id, std::string name);
    std::vector<Category> listCategories();
private:
    DafoeGod& m_theos;
    static inline int s_id{0};

};

#endif
