#ifndef EMPLOYEE_2329
#define EMPLOYEE_2329
#include <string>
#include <string_view>

class Employee{
public:
   Employee(const int id, const std::string& name, const std::string& cargo);

   //Setters
   bool setName(std::string name);
   bool setCargo(std::string cargo);

   //Getters
   std::string_view getName();
   std::string_view getCargo();

private:
   int m_id{};
   std::string m_name{};
   std::string m_cargo{};
   
};
#endif
