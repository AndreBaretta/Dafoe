#include "EmployeeDAO.hpp"

EmployeeDAO::EmployeeDAO( DafoeGod& dafoe)
: m_theos{dafoe}
{}

bool EmployeeDAO::createEmployee(const std::string& name, const std::string& cargo){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into employee (name, cargo) values (?,?)")};
   stmt->setString(1, name);
   stmt->setString(2, cargo);
   stmt->executeQuery();

   return true;

}

bool EmployeeDAO::deleteEmployee(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("delete from employee where id = ?")};
   stmt->setInt(1, id);
   stmt->executeQuery();

   return true;
}

bool EmployeeDAO::updateEmployee(const int id, const std::string& name, const std::string& cargo){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("update employee set (name = ?, cargo = ?) where id = ?")};
   stmt->setString(1, name);
   stmt->setString(2, cargo);
   stmt->setInt(3, id);
   stmt->executeQuery();

   return true;
}

std::vector<Employee> EmployeeDAO::retrieveEmployeeByName(const std::string& name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from employee where name like ?")};
   stmt->setString(1, '%' + name + '%');
   sql::ResultSet* result{stmt->executeQuery()};

   std::vector<Employee> employees{};

   while(result->next()){
      int id = result->getInt("id");
      std::string name = result->getString("name").c_str();
      std::string occupation = result->getString("cargo").c_str();
      Employee employee = Employee(id,name,occupation);
      employees.push_back(employee);

   }

   return employees;
}

std::vector<Employee> EmployeeDAO::retrieveEmployee(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from employee where id = ?")};
   stmt->setInt(1, id);
   sql::ResultSet* result{stmt->executeQuery()};
   std::vector<Employee> employee{};
   if(!result->next())
      return employee;

   int employeeId = result->getInt("id");
   std::string name = result->getString("name").c_str();
   std::string cargo = result->getString("cargo").c_str();

   employee.push_back(Employee(employeeId,name,cargo));

   return employee;
}

std::vector<Employee> EmployeeDAO::listEmployees(){
    std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from employee")};
   sql::ResultSet* result{stmt->executeQuery()};
   result->next();
   
   std::vector<Employee> employees{};

   while(result->next()){
      int employeeId = result->getInt("id");
      std::string name = result->getString("name").c_str();
      std::string cargo = result->getString("cargo").c_str();
      Employee employee = Employee(employeeId,name,cargo);
      employees.push_back(employee);
   }

   return employees;
}  






