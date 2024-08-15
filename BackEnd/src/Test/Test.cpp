#include "Test.hpp"


Test::Test(){}
Test::~Test(){}

bool Test::assertInt(int answer, int method){
   if(answer != method){
      this->m_errorCounter++;
      this->m_errorCommands[m_errorCommands.size()] = this->m_commandCounter;
   }
   this->m_commandCounter++;
   return answer == method;
}

bool Test::assertTrue(bool method){
   if(!method){
      this->m_errorCounter++;
      this->m_errorCommands[m_errorCommands.size()] = this->m_commandCounter;
   }
   this->m_commandCounter++;
   return method;
}

bool Test::assertFalse(bool method){
   if(method){
      this->m_errorCounter++;
      this->m_errorCommands[m_errorCommands.size()] = this->m_commandCounter;
   }
   this->m_commandCounter++;
   return !method;
}

bool Test::assertDouble(double answer, double method){
   if(answer != method){
      this->m_errorCounter++;
      this->m_errorCommands[m_errorCommands.size()] = this->m_commandCounter;
   }
   this->m_commandCounter++;
   return answer == method;
}

bool Test::assertString(std::string answer, std::string method){
   if(answer != method){
      this->m_errorCounter++;
      this->m_errorCommands[m_errorCommands.size()] = this->m_commandCounter;
   }
   this->m_commandCounter++;
   return answer == method;
}

bool Test::assertChar(char answer, char method){
   if(answer != method){
      this->m_errorCounter++;
      this->m_errorCommands[m_errorCommands.size()] = this->m_commandCounter;
   }
   this->m_commandCounter++;
   return answer == method;
}

