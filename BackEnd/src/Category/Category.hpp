#ifndef CATEGORY_0048
#define CATEGORY_0048

#include <string>

class Category {
public:
   Category(int id, const std::string& name);

   // Setters
   bool setId(int id);
   bool setName(const std::string& name);

   // Getters
   int getId() const;
   std::string getName() const;

private:
   int m_id{};
   std::string m_name{};
};

#endif

