#ifndef GENERICPRODUCT_0108
#define GENERICPRODUCT_0108

#include <string>
#include <string_view>

class GenericProduct {
public:
   GenericProduct(int id, const std::string& name, int category);

   // Setters
   bool setName(const std::string& name);
   bool setCategory(int category);

   // Getters
   int getId() const;
   std::string getName() const;
   int getCategory() const;

private:
   int m_id{};
   std::string m_name{};
   int m_category{};
};

#endif

