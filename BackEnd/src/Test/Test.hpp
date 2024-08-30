#ifndef TEST_2208
#define TEST_2208
#include <vector>
#include "../API/HTTPRequest/HTTPRequest.hpp"
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

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
      HTTPRequest testCreateProduct(const std::string& name, const int genericProduct, const int manufacturer,
                                    const std::string& barcode, const double price, const double cost,
                                    const std::string& reference, const int quantity);
      HTTPRequest testDeleteProduct(const int id);
      HTTPRequest testUpdateProduct(const int id, const std::string& name, const int genericProduct,
                                    const int manufacturer, const std::string& barcode, const double price,
                                    const double cost, const std::string& reference, const int quantity);
      HTTPRequest testRetrieveProductById(const int id);
      HTTPRequest testRetrieveProductByReference(const std::string& reference);
      HTTPRequest testRetrieveProductByBarcode(const std::string& barcode);
      HTTPRequest testQueryProductByName(const std::string& name);

      HTTPRequest testRetrieveAllCategories();
      HTTPRequest testRetrieveCategory(const int id);
      HTTPRequest testCreateCategory(const std::string& name);
      HTTPRequest testUpdateCategory(const int id, const std::string& name);
      HTTPRequest testDeleteCategory(const int id);

      HTTPRequest testRetrieveAllPaymentMethod();
      HTTPRequest testRetrievePaymentMethod(const int id);
      HTTPRequest testCreatePaymentMethod(const std::string& name);
      HTTPRequest testUpdatePaymentMethod(const int id, const std::string& name);
      HTTPRequest testDeletePaymentMethod(const int id);

   private:
      int m_commandCounter{};
      int m_errorCounter{};
      std::vector<int> m_errorCommands{};
};


#endif

