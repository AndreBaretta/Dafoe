#ifndef PRODUCT_2211
#define PRODUCT_2211

#include <string>
#include <string_view>
#include <array>
class Product{
   public:
      explicit Product(int id, std::string name, double price);
      explicit Product(int id, std::string name, double price, int quantity);
      explicit Product(int id, std::string name, double price, int quantity, std::array<char, 13> barCode);
      ~Product();

      // Setters
      bool setName(std::string);
      bool setQuantity(int);
      bool setPrice(double);

      // Getters
      int getId();
      std::string_view getName();
      int getQuantity();
      double getPrice();
      std::array<char, 13>& getBarCode();
      

   private:
      int m_id{};
      std::string m_name{};
      int m_quantity{};
      double m_price{};
      std::array<char, 13> m_barCode{};
      bool setId(int);
      bool setBarCode(std::array<char, 13>);

};
#endif

