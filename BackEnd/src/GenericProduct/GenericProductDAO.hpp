#ifndef GENERICPRODUCTDAO_1522
#define GENERICPRODUCTDAO_1522

#include "../DafoeGod/DafoeGod.hpp"
#include "GenericProduct.hpp"

class GenericProductDAO{
public:
   GenericProductDAO(DafoeGod& dafoe);
   bool createGenericProduct(const std::string& name, const int quantity, const int category, const std::string& reference);
   bool deleteGenericProduct(const int id);
   bool updateGenericProduct(const int id, const std::string& name, const int quantity, const int category, const std::string& reference);
   std::vector<GenericProduct> retrieveGenericProductByName(const std::string& name);

   private:
   DafoeGod& m_theos;

};


#endif
