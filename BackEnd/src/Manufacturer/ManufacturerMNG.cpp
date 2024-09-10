#include "ManufacturerMNG.hpp"

ManufacturerMNG::ManufacturerMNG(ManufacturerDAO& manufacturerDAO, JsonBuilder& jsonBuilder)
: m_manufacturerDAO{manufacturerDAO}
, m_jsonBuilder{jsonBuilder}
{}

json ManufacturerMNG::retrieveAllManufacturer(){
   try{
   std::vector<Manufacturer> manufacturers = this->m_manufacturerDAO.listAllManufacturer();
   json json = this->m_jsonBuilder.manufacturerVectorToJson(manufacturers);
   return json;
   }catch(std::exception &e){
      throw;
   }
}

json ManufacturerMNG::retrieveManufacturer(const int id){
   try{
   std::vector<Manufacturer> manufacturer = this->m_manufacturerDAO.retrieveManufacturer(id);
   json json = this->m_jsonBuilder.manufacturerVectorToJson(manufacturer);
   return json;
   }catch(std::exception &e){
      throw;
   }
}

json ManufacturerMNG::retrieveManufacturerByName(const std::string& name){
   try{
   std::vector<Manufacturer> manufacturers = this->m_manufacturerDAO.retrieveManufacturerByName(name);
   json json = this->m_jsonBuilder.manufacturerVectorToJson(manufacturers);
   return json;
   }catch(std::exception &e){
      throw;
   }
}

bool ManufacturerMNG::createManufacturer(const std::string& name){
   bool response = this->m_manufacturerDAO.createManufacturer(name);
   return response;
}

bool ManufacturerMNG::updateManufacturer(const int id, const std::string& name){
   bool response = this->m_manufacturerDAO.updateManufacturer(id,name);
   return response;
}

bool ManufacturerMNG::deleteManufacturer(const int id){
   bool response = this->m_manufacturerDAO.deleteManufacturer(id);
   return response;
}

