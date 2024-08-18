#include "Category.hpp"
#include <vector>

class CategoryDAO{
public:
    bool createCategory(std::string name);
    bool deleteCategory();
    bool updateCategory();
    std::vector<Category> listCategories();
private:
    static inline int s_id{0};

};


