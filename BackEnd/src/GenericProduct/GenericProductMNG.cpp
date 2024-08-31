#include "GenericProductMNG.hpp"
#include "GenericProduct.hpp"
#include "GenericProductDAO.hpp"
GenericProductMNG::GenericProductMNG(GenericProductDAO& gpdao, JsonBuilder& jason)
: m_gPDAO{gpdao}
, m_jsonBuilder{jason}
{}

bool GenericProductMNG::createGenericProduct(const std::string& name, const int quantity, const int category, const std::string& reference){
   m_gPDAO.createGenericProduct(name, quantity, category, reference);
   return true;
}


bool GenericProductMNG::deleteGenericProduct(const int id){
   m_gPDAO.deleteGenericProduct(id);
   return true;
}


bool GenericProductMNG::updateGenericProduct(const int id, const std::string& name, const int quantity, const int category, const std::string& reference){
   m_gPDAO.updateGenericProduct(id, name, quantity, category, reference);
   return true;
}


json GenericProductMNG::retrieveGenericProductByName(const std::string& name){
   std::vector<GenericProduct> vec{this->m_gPDAO.retrieveGenericProductByName(name)};
   json json {this->m_jsonBuilder.genericProductVectorToJson(vec)};
   return json;
}
