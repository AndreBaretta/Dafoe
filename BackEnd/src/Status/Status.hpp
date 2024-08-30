#ifndef STATUS_1410
#define STATUS_1410

#include <string>
class Status{
public:
   Status(int id, const std::string& name);

   //setters
   bool setName(const std::string& name);

   //getters
   int getId();
   std::string& getName(); 

private:
   int m_id{};
   std::string m_name{};
};
#endif
