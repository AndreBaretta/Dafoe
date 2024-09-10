#ifndef JSONBUILDER_0035
#define JSONBUILDER_0035
#include "../../Product/Product.hpp"
#include "../../Category/Category.hpp"
#include "../../PaymentMethod/PaymentMethod.hpp"
#include "../../Employee/Employee.hpp"
#include "../../Manufacturer/Manufacturer.hpp"
#include "../../Status/Status.hpp"
#include "../../SellOrder/SellOrder.hpp"
#include "../../GenericProduct/GenericProduct.hpp"
#include "../../ProductOrder/ProductOrder.hpp"
#include "../../Client/Client.hpp"
#include <vector>
#include <map>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class JsonBuilder{
   public:
      JsonBuilder();
      ~JsonBuilder();
      json productToJson(Product& product);
      json productVectorToJson(std::vector<Product>& products);
      json categoryToJson(Category& category);
      json categoryVectorToJson(std::vector<Category>& categories);
      json paymentMethodToJson(PaymentMethod& paymentMethod);
      json paymentMethodVectorToJson(std::vector<PaymentMethod>& paymentMethods);
      json employeeToJson(Employee& employee);
      json employeeVectorToJson(std::vector<Employee>& employees);
      json manufacturerToJson(Manufacturer& manufacturer);
      json manufacturerVectorToJson(std::vector<Manufacturer>& manufacturers);
      json statusToJson(Status& status);
      json statusVectorToJson(std::vector<Status>& statuses);
      json sellOrderToJson(SellOrder& sellOrder);
      json sellOrderVectorToJson(std::vector<SellOrder>& sellOrders);
      json genericProductToJson(GenericProduct& genericProduct);
      json genericProductVectorToJson(std::vector<GenericProduct>& genericProducts);
      json productOrderToJson(ProductOrder& productOrder);
      json productOrderVectorToJson(std::vector<ProductOrder>& productOrders);
      std::vector<ProductOrder> jsonToProductOrderVector(json json, int order);
      json clientToJson(Client& client);
      json clientVectorToJson(std::vector<Client>& clients);
      
};


#endif
