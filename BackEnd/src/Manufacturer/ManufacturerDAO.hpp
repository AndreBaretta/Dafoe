
#ifndef MANUFACTURERDAO_0138
#define MANUFACTURERDAO_0138

#include "Manufacturer.hpp"
#include "../DafoeGod/DafoeGod.hpp"


class ManufacturerDAO{
public:
   ManufacturerDAO(DafoeGod& dafoe);
   bool createManufacturer(const std::string& name);
   std::vector<Manufacturer> retrieveManufacturerByName(const std::string& name);
   bool updateManufacturer(const int id, const std::string& name);
   bool deleteManufacturer(const int id);
   std::vector<Manufacturer> listAllManufacturer();
   std::vector<Manufacturer> retrieveManufacturer(const int id);

private:
   DafoeGod& m_theos;
};


#endif
