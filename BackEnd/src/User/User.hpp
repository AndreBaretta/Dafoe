#ifndef USER_0250
#define USER_0250

#include <string>

class User {
public:
    User(const int id, const std::string& name, const std::string& password);

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getPassword() const;

    // Setters
    void setId(int id);
    void setName(const std::string& name);
    void setPassword(const std::string& password);

private:
    int m_id{};
    std::string m_name{};
    std::string m_password{};
};

#endif 

