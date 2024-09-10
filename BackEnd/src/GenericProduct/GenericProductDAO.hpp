#ifndef GENERICPRODUCTDAO_1522
#define GENERICPRODUCTDAO_1522

#include "../DafoeGod/DafoeGod.hpp"
#include "GenericProduct.hpp"

class GenericProductDAO{
public:
   GenericProductDAO(DafoeGod& dafoe);
   bool createGenericProduct(const std::string& name, const int category);
   bool deleteGenericProduct(const int id);
   bool updateGenericProduct(const int id, const std::string& name, const int category);
   std::vector<GenericProduct> retrieveGenericProductByName(const std::string& name);
   std::vector<GenericProduct> retrieveGenericProduct();

   private:
   DafoeGod& m_theos;

};


#endif
