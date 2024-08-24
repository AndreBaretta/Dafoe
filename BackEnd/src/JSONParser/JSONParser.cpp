#include "JSONParser.hpp"
#include <cstddef>
#include <stdexcept>
#include <unordered_map>
#include "functions.hpp"

JSONNode::JSONNode(JSONType type)
: m_type{type}
{}

JSONNode::JSONNode()
: m_type{JSONType::NULLT}
{};

JSONNode::JSONNode(std::nullptr_t) 
: JSONNode()
{};

JSONNode::JSONNode(int value)
: m_type{JSONType::NUMBER}
{
   m_value.m_number = value;
}

JSONNode::JSONNode(double value) 
: m_type{JSONType::NUMBER}
{
   m_value.m_number = value;
}

JSONNode::JSONNode(const std::vector<JSONNode>& nodes)
   : m_array{nodes}
   , m_type{JSONType::ARRAY}
{}

JSONNode::JSONNode(const std::string& value)
: m_type{JSONType::STRING}
{
   m_value.m_string = value;
}

JSONNode::JSONNode(const char* value)
: m_type{JSONType::ARRAY}
{
   m_value.m_string = value;
}

JSONNode::JSONNode(bool value)
: m_type{JSONType::BOOL}
{
   m_value.m_bool = value;
}

JSONNode::JSONNode(const JSONNode& node)
{
   m_type  = node.m_type;
   m_data  = node.m_data;
   m_array = node.m_array;

   m_value.m_bool   = node.m_value.m_bool;
   m_value.m_string = node.m_value.m_string;
   m_value.m_number = node.m_value.m_number;

}

JSONNode& JSONNode::operator=(const JSONNode& node)
{
   m_type  = node.m_type;
   m_data  = node.m_data;
   m_array = node.m_array;

   m_value.m_bool   = node.m_value.m_bool;
   m_value.m_string = node.m_value.m_string;
   m_value.m_number = node.m_value.m_number;
   return *this;
}

JSONNode::value::value(){};
JSONNode::value::~value(){};

bool JSONNode::isValue(){
   return m_type == JSONType::BOOL ||
   m_type == JSONType::NUMBER ||
   m_type == JSONType::STRING ||
   m_type == JSONType::NULLT;
}

bool JSONNode::isObject(){
   return m_type == JSONType::OBJECT;
}

bool JSONNode::isArray(){
   return m_type == JSONType::ARRAY;
}

bool JSONNode::isNull(){
   return m_type == JSONType::NULLT;
}

void JSONNode::appendArray(const JSONNode& node){
   m_array.push_back(node);
}

template<typename T>

T JSONNode::get(){
   if(!isValue()){
      throw std::runtime_error("unable to get value for this type");
   }
   return static_cast<T>(m_value);
}

void JSONNode::limitToArray(){
   if(!isArray()){
      throw std::runtime_error("this operation is only available to array node");
   }

};

void JSONNode::limitToObject(){
   if(!isObject()){
      throw std::runtime_error("this operation is only available to object node");
   }
}


JSONNode& JSONNode::operator[](int index){
   limitToArray();
   return m_array[index];
}

JSONNode& JSONNode::operator[](const std::string& str){
   limitToObject();
   return m_data[str];
}

JSONNode& JSONNode::operator[](const char* key){
   limitToObject();
   return m_data[key];
}

JSONNode::operator std::string(){
   return m_value.m_string;
}

JSONNode::operator double(){
   return m_value.m_number;
}

JSONNode::operator int(){
   return m_value.m_number;
}

JSONNode::operator bool(){
   return m_value.m_bool;
}

JSONNode JSONNode::parseObject(const std::string& str, int start, int end, std::unordered_map<int, int>& bracePair){
   int i {start};

   JSONNode ans{JSONType::OBJECT};

   while(i < end){
      while(str[i] != '"'){
         ++i;
      }  

      ++i;

      std::string key {};

      while(str[i] != '"'){
         key += str[i];
         ++i;
      }

      while(str[i] != ':'){
         ++i;
      }

      while(isWhitespace(str[i])){
         ++i;
      }

      std::string value{};

      if(str[i] == '{'){
         ans[key] = parseObject(str, i, bracePair[i], bracePair);
         i = bracePair[i] + 1;
         continue;
      }

      else if(str[i] == '['){
         ans[key] = parseArray(str, i, bracePair[i], bracePair);
         i = bracePair[i] + 1;
         continue;
      }

      while(i < end && str[i] != ','){
         value += str[i];
         ++i;
      }

      ans[key] = getValue(value);
   }

   return ans;

}



JSONNode JSONNode::parseArray(const std::string& str, int start, int end, std::unordered_map<int, int>& bracePair){
   int i {start};

   JSONNode ans{JSONType::ARRAY};
   ++i;

   while(i < end){
      while(!isWhitespace(str[i])){
         ++i;
      }

      std::string value{};

      while(i < end && str[i] != ','){
         value += str[i];
         ++i;
      }

      ++i;
      ans.appendArray(getValue(value));
   }

   return ans;

}

JSONNode JSONNode::parse(const std::string& str){
   std::unordered_map<int, int> bracePair{};
   findBracesPairs(str, bracePair);

   int i {};

   while(isWhitespace(str[i])){
      ++i;
   }

   if(str[i] == '['){
      return parseArray(str, i, bracePair[i], bracePair);

   }

   return parseObject(str, i, bracePair[i], bracePair);
}

std::string JSONNode::stringify(const JSONNode& node){
   switch (node.m_type){
      case JSONType::BOOL:
         return node.m_value.m_bool ? "true" : "false";
      case JSONType::NULLT:
         return "null";
      case JSONType::NUMBER:
         return std::to_string(node.m_value.m_number);
      case JSONType::STRING:{
         std::string answer {"\""};
         answer += node.m_value.m_string;
         answer += '"';
         return answer;
      }
      case JSONType::ARRAY:{
         std::string answer{"["};
         for(auto v : node.m_array){
            answer += stringify(v);
            answer += ',';
         }
         answer[answer.length()-1] = ']';
         return answer;
      }
      case JSONType::OBJECT:{
         std::string answer{"{"};
         for(auto &c : node.m_data){
            answer += '"' ;
            answer += c.first;
            answer += '"';
            answer += ':';
            answer += stringify(c.second);
            answer += ',';
         }
         answer[answer.length()-1] = '}';
         return answer;
      }

   }

   return "error";
}



