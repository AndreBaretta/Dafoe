#include "GenericProductMNG.hpp"
#include "GenericProduct.hpp"
#include "GenericProductDAO.hpp"
GenericProductMNG::GenericProductMNG(GenericProductDAO& gpdao, JsonBuilder& jason)
: m_gPDAO{gpdao}
, m_jsonBuilder{jason}
{}

bool GenericProductMNG::createGenericProduct(const std::string& name, const int category){
   m_gPDAO.createGenericProduct(name, category);
   return true;
}


bool GenericProductMNG::deleteGenericProduct(const int id){
   m_gPDAO.deleteGenericProduct(id);
   return true;
}


bool GenericProductMNG::updateGenericProduct(const int id, const std::string& name, const int category){
   m_gPDAO.updateGenericProduct(id, name, category);
   return true;
}


json GenericProductMNG::retrieveGenericProductByName(const std::string& name){
   std::vector<GenericProduct> vec{this->m_gPDAO.retrieveGenericProductByName(name)};
   json json = this->m_jsonBuilder.genericProductVectorToJson(vec);
   return json;
}

json GenericProductMNG::retrieveGenericProduct(){
   std::vector<GenericProduct> vec{this->m_gPDAO.retrieveGenericProduct()};
   json json = this->m_jsonBuilder.genericProductVectorToJson(vec);
   return json;
}
