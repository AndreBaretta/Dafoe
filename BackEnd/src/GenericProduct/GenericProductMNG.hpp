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
   bool createGenericProduct(const std::string& name, const int quantity, const int category, const std::string& reference);
   bool deleteGenericProduct(const int id);
   bool updateGenericProduct(const int id, const std::string& name, const int quantity, const int category, const std::string& reference);
   json retrieveGenericProductByName(const std::string& name);

private:
   GenericProductDAO& m_gPDAO;
   JsonBuilder& m_jsonBuilder;
};

#endif
