#ifndef FUNCTIONS_2022
#define FUNCTIONS_2022

#include "JSONParser.hpp"
#include <cctype>
#include <cstddef>
#include <string>
#include <unordered_map>

void findBracesPairs(const std::string& str, std::unordered_map<int, int>& bracePair){
   std::vector<int> something{};

   std::size_t n{str.length()};

   for(int i = 0; i < n; ++i){
      if(str[i] == '[' || str[i] == '{'){
         something.push_back(i);
      }

      else if(str[i] == ']' || str[i] == '}'){
         bracePair[something.back()] = i;
         something.pop_back();
      }
   }

}

bool isWhitespace(char c){
   return c == ' ' || c == '\n';
}

bool isDouble(const std::string& str){
   int i{};

   if(str[0] == '+' || str[0] == '-'){
      ++i;
   }

   bool dotSenn {false};

   while(i < str.length()){
      if(!std::isdigit(str[i]) && str[i] != '.'){
         return false;
      }

      if(str[i] == '.'){
         if(dotSenn){
            return false;
         }
         dotSenn = true;

      }
      ++i;

   }

   return true;
}

bool isInteger(const std::string& str){
   int i{};

   if(str[0] == '+' || str[0] == '-'){
      ++i;
   }

   while(i < str.length()){
      if(!std::isdigit(str[i])){
         return false;
      }
      ++i;
   }

   return true;
}

JSONNode getValue(const std::string& str){
   int i {};
   std::size_t j {str.length()-1};

   while(isWhitespace(str[i])){
      ++i;
   }

   while(isWhitespace(str[j])){
      --j;
   }

   std::string temp{str.substr(i, j-i +1)};

   if(temp[0] =='"'){
      return JSONNode(temp.substr(1, temp.length()-2));
   }

   if(temp == "true" || temp == "false"){
      return JSONNode(str=="true");
   }

   if(temp == "null"){
      return JSONNode();
   }

   if(isDouble(temp)){
      return JSONNode(std::stod(temp));
   }

   if(isInteger(temp)){
      return JSONNode(std::stoi(temp));
   }
   
   return JSONNode(temp);
}

#endif
