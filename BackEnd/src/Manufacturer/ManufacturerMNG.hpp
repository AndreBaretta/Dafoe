#ifndef MANUFACTURERMNG_0224
#define MANUFACTURERMNG_0224
#include "ManufacturerDAO.hpp"
#include "Manufacturer.hpp"
#include "../API/Json/JsonBuilder.hpp"
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ManufacturerMNG{
public:
   ManufacturerMNG(ManufacturerDAO& manufacturerDAO, JsonBuilder& jsonBuilder);
   json retrieveAllManufacturer();
   json retrieveManufacturer(const int id);
   json retrieveManufacturerByName(const std::string& name);
   bool createManufacturer(const std::string& name);
   bool deleteManufacturer(const int id);
   bool updateManufacturer(const int id, const std::string& name);

private:
   ManufacturerDAO& m_manufacturerDAO;
   JsonBuilder& m_jsonBuilder;
};

#endif
