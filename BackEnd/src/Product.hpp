#include <iostream>

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
      std::string name{};
      int quantity{};
}


