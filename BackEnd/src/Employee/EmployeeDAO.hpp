#ifndef EMPLOYEEDAO_2342
#define EMPLOYEEDAO_2342
#include "../DafoeGod/DafoeGod.hpp"

class EmployeeDAO{
   public:

   EmployeeDAO(DafoeGod& dafoe);

   bool createEmployee(const std::string& name, const std::string& cargo);
   bool updateEmployee(const int id,const std::string& name, const std::string& cargo);
   bool deleteEmployee(const int id);
   std::vector<std::map<std::string, std::string>> retrieveEmployeeByName(const std::string& name); 


   private:
   DafoeGod& m_theos;
};
#endif
