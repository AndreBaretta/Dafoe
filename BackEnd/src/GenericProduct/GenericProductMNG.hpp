#ifndef GENERICPRODUCTMNG_0216
#define GENERICPRODUCTMNG_0216
#include "GenericProductDAO.hpp"
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include "../API/Json/JsonBuilder.hpp"
using json = nlohmann::json;

class GenericProductMNG{
public:
   GenericProductMNG(GenericProductDAO& gpdao, JsonBuilder& jason);
   bool createGenericProduct(const std::string& name, const int category);
   bool deleteGenericProduct(const int id);
   bool updateGenericProduct(const int id, const std::string& name, const int category);
   json retrieveGenericProductByName(const std::string& name);
   json retrieveGenericProduct();

private:
   GenericProductDAO& m_gPDAO;
   JsonBuilder& m_jsonBuilder;
};

#endif
