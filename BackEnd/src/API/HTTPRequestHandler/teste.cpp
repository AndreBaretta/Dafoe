#include <vector>
#include <string>
#include <sstream>

int main(){
   std::string path = "api/product/2";
   std::istringstream tempPath{path};
   std::string buffer;
   std::vector<std::string> vPath;
   while(getline(tempPath,buffer,'/')){
      vPath.push_back(buffer);
   }
   return 1;
}

