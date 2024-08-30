#ifndef GENERICPRODUCT_0108
#define GENERICPRODUCT_0108

#include <string>
#include <string_view>

class GenericProduct {
public:
   GenericProduct(int id, const std::string& name, int quantity, int category, const std::string& reference);

   // Setters
   bool setName(const std::string& name);
   bool setQuantity(int quantity);
   bool setCategory(int category);
   bool setReference(const std::string& reference);

   // Getters
   int getId() const;
   std::string_view getName() const;
   int getQuantity() const;
   int getCategory() const;
   std::string_view getReference() const;

private:
   int m_id{};
   std::string m_name{};
   int m_quantity{};
   int m_category{};
   std::string m_reference{};
};

#endif

