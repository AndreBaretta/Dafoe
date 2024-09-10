#include "EmployeeDAO.hpp"
#include <iostream>

EmployeeDAO::EmployeeDAO( DafoeGod& dafoe)
: m_theos{dafoe}
{}

bool EmployeeDAO::createEmployee(const std::string& name, const std::string& cargo){
   try{
      m_theos.prepareStatement("insert into employee (name, cargo) values (?,?)");
      m_theos.getStatement()->setString(1, name);
      m_theos.getStatement()->setString(2, cargo);
      m_theos.query(CREATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

bool EmployeeDAO::deleteEmployee(const int id){
   try{
      m_theos.prepareStatement("delete from employee where id = ?");
      m_theos.getStatement()->setInt(1, id);
      m_theos.query(DELETE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

bool EmployeeDAO::updateEmployee(const int id, const std::string& name, const std::string& cargo){
   try{
      m_theos.prepareStatement("update employee set name = ?, cargo = ? where id = ?");
      m_theos.getStatement()->setString(1, name);
      m_theos.getStatement()->setString(2, cargo);
      m_theos.getStatement()->setInt(3, id);
      m_theos.query(UPDATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

}

std::vector<Employee> EmployeeDAO::retrieveEmployeeByName(const std::string& name){
   try{
      m_theos.prepareStatement("select * from employee where name like ?");
      m_theos.getStatement()->setString(1, '%' + name + '%');
      m_theos.query(RETRIEVE);

      std::vector<Employee> employees{};

      while(m_theos.getResult()->next()){

         int id = m_theos.getResult()->getInt("id");
         std::string name = m_theos.getResult()->getString("name").c_str();
         std::string occupation = m_theos.getResult()->getString("cargo").c_str();
         Employee employee = Employee(id,name,occupation);
         employees.push_back(employee);

      }

      return employees;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<Employee> EmployeeDAO::retrieveEmployee(const int id){
   try{
      m_theos.prepareStatement("select * from employee where id = ?");
      m_theos.getStatement()->setInt(1, id);
      m_theos.query(RETRIEVE);

      std::vector<Employee> employee{};

      if(!m_theos.getResult()->next())
         return employee;

      int employeeId = m_theos.getResult()->getInt("id");
      std::string name = m_theos.getResult()->getString("name").c_str();
      std::string cargo = m_theos.getResult()->getString("cargo").c_str();

      employee.push_back(Employee(employeeId,name,cargo));

      return employee;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<Employee> EmployeeDAO::listEmployees(){
   try{
      m_theos.prepareStatement("select * from employee");
      m_theos.query(RETRIEVE); 

      std::vector<Employee> employees{};

      while(m_theos.getResult()->next()){
         int employeeId = m_theos.getResult()->getInt("id");
         std::string name = m_theos.getResult()->getString("name").c_str();
         std::string cargo = m_theos.getResult()->getString("cargo").c_str();
         Employee employee = Employee(employeeId,name,cargo);
         employees.push_back(employee);
      }

      return employees;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

}  

