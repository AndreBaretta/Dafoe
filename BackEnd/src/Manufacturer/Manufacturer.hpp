#ifndef MANUFACTURER19_59
#define MANUFACTURER19_59
#include <string>
class Manufacturer{
public:
    Manufacturer(int id, std::string name);
    explicit Manufacturer(int id);
    //Setters

    //Getters
    int getId();

private:
    int m_id{};
    std::string m_name{};
};

#endif
