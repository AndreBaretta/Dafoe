#ifndef PRODUCT_2211
#define PRODUCT_2211
#include <string>

class Product{
   public:
      Product();
      Product(const int id, const std::string& name, const int genericProduct, const int manufacturer, const std::string& barcode, 
              const double price, const double cost, const std::string& reference, const int quantity);

      // Setters
      bool setId(int id);
      bool setName(std::string name);
      bool setGenericProduct(int genericProduct);
      bool setManufacturer(int manufacturer);
      bool setBarcode(std::string barcode);
      bool setPrice(double price);
      bool setCost(double cost);
      bool setReference(std::string reference);
      bool setQuantity(int quantity);

      // Getters
      int getId();
      std::string getName();
      int getGenericProduct();
      int getManufacturer();
      std::string getBarcode();
      double getPrice();
      double getCost();
      std::string getReference();
      int getQuantity();
      

   private:
      int m_id{};
      std::string m_name{};
      int m_genericProduct{};
      int m_manufacturer{};
      std::string m_barcode{};
      double m_price{};
      double m_cost{};
      std::string m_reference{};
      int m_quantity{};
      
};
#endif

