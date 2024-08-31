#include "EmployeeMNG.hpp"

EmployeeMNG::EmployeeMNG(EmployeeDAO& employeeDAO, JsonBuilder& jsonBuilder)
: m_employeeDAO{employeeDAO}
, m_jsonBuilder{jsonBuilder}
{}

json EmployeeMNG::retrieveEmployeeByName(const std::string& name){
   std::vector<Employee> employees = this->m_employeeDAO.retrieveEmployeeByName(name);
   json json = this->m_jsonBuilder.employeeVectorToJson(employees);
   return json;
}

json EmployeeMNG::retrieveAllEmployee(){
   std::vector<Employee> employees = this->m_employeeDAO.listEmployees();
   json json = this->m_jsonBuilder.employeeVectorToJson(employees);
   return json;
}

json EmployeeMNG::retrieveEmployee(const int id){
   Employee employee = this->m_employeeDAO.retrieveEmployee(id);
   json json = this->m_jsonBuilder.employeeToJson(employee);
   return json;
}

bool EmployeeMNG::createEmployee(const std::string& name, const std::string& cargo){
   bool response = this->m_employeeDAO.createEmployee(name, cargo);
   return response;
}

bool EmployeeMNG::updateEmployee(const int id, const std::string& name, const std::string& cargo){
   bool response = this->m_employeeDAO.updateEmployee(id, name, cargo);
   return response;
}

bool EmployeeMNG::deleteEmployee(const int id){
   bool response = this->m_employeeDAO.deleteEmployee(id);
   return response;
}

