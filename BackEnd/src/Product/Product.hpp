#ifndef PRODUCT_2211
#define PRODUCT_2211
#include <string>

class Product{
   public:
      Product();
      Product(const int id, const std::string& name, const std::string& barcode, const double price, const int quantity);
      Product(const int id, const std::string& name, const std::string& barcode, const double price, const double cost, std::string& reference, const int quantity);

      // Setters
      bool setId(int id);
      bool setName(std::string name);
      bool setBarcode(std::string barcode);
      bool setPrice(double price);
      bool setCost(double cost);
      bool setReference(std::string reference);
      bool setQuantity(int quantity);

      // Getters
      int getId();
      std::string getName();
      std::string getBarcode();
      double getPrice();
      double getCost();
      std::string getReference();
      int getQuantity();
      

   private:
      int m_id{};
      std::string m_name{};
      std::string m_barcode{};
      double m_price{};
      double m_cost{};
      std::string m_reference{};
      int m_quantity{};
      
};
#endif

