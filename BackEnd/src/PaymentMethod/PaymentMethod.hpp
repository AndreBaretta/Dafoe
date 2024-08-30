#ifndef PAYMENTMETHOD_0232
#define PAYMENTMETHOD_0232

#include <string>

class PaymentMethod {
public:
    PaymentMethod(int id, const std::string& name);

    // Setters
    bool setId(int id);
    bool setName(const std::string& name);

    // Getters
    int getId() const;
    const std::string& getName() const;

private:
    int m_id{};
    std::string m_name{};
};

#endif

