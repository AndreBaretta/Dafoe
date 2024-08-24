#ifndef GENERICPRODUCT_0108
#define GENERICPRODUCT_0108
#include <string>
#include <string_view>

class GenericProduct{
public:
    GenericProduct(const int id, const std::string& name, const int quantity, const int category, const std::string& reference);

    //Setters
    bool setName(const std::string& name);
    bool setQuantity(const int quantity);
    bool setCategory(const int category);
    bool setReference(const std::string& reference);

    //Getters

    int getId();
    std::string_view getName();
    int getQuantity();
    int getCategory();
    std::string_view getReference();

private:
    int m_id{};
    std::string m_name{};
    int m_quantity{};
    int m_category{};
    std::string m_reference{};
};

#endif
