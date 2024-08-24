#ifndef MANUFACTURER19_59
#define MANUFACTURER19_59
#include <string>

class Manufacturer{
public:
   Manufacturer(int id, const std::string& name);
   //Setters
   bool setName(const std::string& name);

   //Getters
   int getId();
   std::string_view getName();

private:
   int m_id{};
   std::string m_name{};
};

#endif
