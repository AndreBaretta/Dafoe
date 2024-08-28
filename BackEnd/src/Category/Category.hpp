#ifndef CATEGORY_0048
#define CATEGORY_0048

#include <string>
class Category{
public:
   Category(int id, std::string name);

   // Setters
   bool setId(const int id);
   bool setName(const std::string& name);

   // Getters
   std::string getName();
   int getId();

private:
   std::string m_name{};
   int m_id{};

};

#endif
