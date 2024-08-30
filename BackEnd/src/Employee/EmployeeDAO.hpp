#ifndef EMPLOYEEDAO_2342
#define EMPLOYEEDAO_2342
#include "../DafoeGod/DafoeGod.hpp"
#include "Employee.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <memory>

class EmployeeDAO{
   public:
      EmployeeDAO(DafoeGod& dafoe);
      bool createEmployee(const std::string& name, const std::string& cargo);
      bool updateEmployee(const int id,const std::string& name, const std::string& cargo);
      bool deleteEmployee(const int id);
      std::vector<Employee> retrieveEmployeeByName(const std::string& name); 
      std::vector<Employee> listEmployees();
      Employee retrieveEmployee(const int id);

   private:
      DafoeGod& m_theos;
};
#endif
