#ifndef PRODUCT_2211
#define PRODUCT_2211

#include <string>
#include <string_view>

class Product{
   public:
      Product(int, std::string, double);
      ~Product();

      // Setters
      bool setId(int);
      bool setName(std::string);
      bool setQuantity(int);
      bool setPrice(double);
      bool setBarCode(int);

      // Getters
      int getId();
      std::string_view getName();
      int getQuantity();
      double getPrice();
      

   private:
      int id{};
      std::string name{};
      int quantity{};
      double price{};
      char barCode[13];

};
#endif

