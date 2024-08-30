#ifndef EMPLOYEEMNG_0150
#define EMPLOYEEMNG_0150
#include "EmployeeDAO.hpp"
#include "Employee.hpp"
#include "../API/Json/JsonBuilder.hpp"
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class EmployeeMNG{
   public:
      EmployeeMNG(EmployeeDAO& employeeDAO, JsonBuilder& jsonBuilder);
      json retrieveEmployeeByName(const std::string& name);
      json retrieveAllEmployees();
      json retrieveEmployee(const int id);
      bool createEmployee(const std::string& name, const std::string& cargo);
      bool deleteEmployee(const int id);
      bool updateEmployee(const int id, const std::string& name, const std::string& cargo);

   private:
      EmployeeDAO& m_employeeDAO;
      JsonBuilder& m_jsonBuilder;
};

#endif
