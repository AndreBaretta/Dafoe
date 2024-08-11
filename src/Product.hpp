#ifndef PRODUCT_2211
#define PRODUCT_2211

#include <string>

class Product{
   public:
      Product(){}
      ~Product(){}

      // Setters
      bool setId(int);
      bool setName(std::string);
      bool setQuantity(int);

      // Getters
      int getId();
      std::string getName();
      int getQuantity();

   private:
      int id{};
      int barCode{};
      std::string name{};
      int quantity{};
};
#endif

