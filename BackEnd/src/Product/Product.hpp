#ifndef PRODUCT_2211
#define PRODUCT_2211

#include <string>
#include <string_view>
#include <array>
class Product{
   public:
      Product(const int id, const std::string& name);
      Product(const int id, const std::string& name,const int quantity);
      Product(const int id, const std::string& name, const int quantity, const int category);

      // Setters
      bool setName(std::string name);
      bool setQuantity(int qnty);
      bool setId(int id);
      // Getters
      int getId();
      std::string_view getName();
      int getQuantity();
      std::array<char, 13>& getBarCode();
      

   private:
      int m_id{};
      std::string m_name{};
      int m_quantity{};
      int m_category{};
      
};
#endif

