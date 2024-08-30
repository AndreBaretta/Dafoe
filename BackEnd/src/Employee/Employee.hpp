#ifndef EMPLOYEE_2329
#define EMPLOYEE_2329

#include <string>
#include <string_view>

class Employee {
public:
   // Constructor
   Employee(int id, const std::string& name, const std::string& cargo);

   // Setters
   bool setId(const int id);
   bool setName(const std::string& name);
   bool setCargo(const std::string& cargo);

   // Getters
   int getId() const;
   std::string_view getName() const;
   std::string_view getCargo() const;

private:
   int m_id{};
   std::string m_name{};
   std::string m_cargo{};
};

#endif

