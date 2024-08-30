#ifndef CLIENT_2208
#define CLIENT_2208

#include <string>
#include <string_view>

class Client {
public:
    Client(int id, const std::string& name, const std::string& phoneNumber, const std::string& address, double bill);

    // Setters
    bool setName(const std::string& name);
    bool setAddress(const std::string& address);
    bool setBill(double bill);

    // Getters
    int getId() const;
    std::string_view getName() const;
    std::string_view getAddress() const;
    double getBill() const;

private:
    int m_id{};
    std::string m_name{};
    std::string m_address{};
    double m_bill{};
    std::string m_phoneNumber{};
};

#endif

