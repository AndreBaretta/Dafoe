#ifndef MANUFACTURER19_59
#define MANUFACTURER19_59

#include <string>

class Manufacturer {
public:
    Manufacturer(int id, const std::string& name);
    
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

