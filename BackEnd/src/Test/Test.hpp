#ifndef TEST_2208
#define TEST_2208
#include <vector>
#include <string>

class Test{
   public:
      Test();
      ~Test();
      bool assertTrue(bool method);
      bool assertFalse(bool method);
      bool assertInt(int answer, int method);
      bool assertDouble(double answer, double method);
      bool assertString(std::string answer, std::string method);
      bool assertChar(char answer, char method);

   private:
      int m_commandCounter{};
      int m_errorCounter{};
      std::vector<int> m_errorCommands{};
};


#endif

