#ifndef STATUS_2048
#define STATUS_2048
#include <string>

class Status{
public:
   Status(int id, std::string name);

private:
   int m_id{};
   std::string m_name{};
};

#endif
