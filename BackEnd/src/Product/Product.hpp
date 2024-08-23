#ifndef PRODUCT_2211
#define PRODUCT_2211
#include <string>

class Product{
   public:
      Product(const int id, const std::string& name);
      Product(const int id, const std::string& name, const int quantity);
      Product(const int id, const std::string& name, const int quantity, const int category);

      // Setters
      bool setName(std::string name);
      bool setQuantity(int qnty);
      bool setId(int id);
      bool setBarCode(std::string barcode);
      bool setCategory(std::string category);

      // Getters
      int getId();
      std::string getName();
      int getQuantity();
      std::string getCategory();
      std::string getBarCode();
      

   private:
      int m_id{};
      std::string m_name{};
      int m_quantity{};
      int m_category{};
      std::string m_barcode{};
      
};
#endif

