#ifndef JSONPARSER_1542
#define JSONPARSER_1542

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

enum class JSONType : int{
    NUMBER,
    STRING,
    NULLT,
    OBJECT,
    ARRAY,
    BOOL,

};

class JSONNode{
public:

    JSONNode(JSONType type);
    JSONNode();
    JSONNode(std::nullptr_t);
    JSONNode(int value);
    JSONNode(double value);
    JSONNode(const std::vector<JSONNode>& nodes);
    JSONNode(const std::string& value);
    JSONNode(const char* value);
    JSONNode(bool value);
    JSONNode(const JSONNode& node);
    JSONNode& operator=(const JSONNode& node);
    
    bool isValue();
    bool isObject();
    bool isArray();
    bool isNull();
    void appendArray(const JSONNode& node);

    template<typename T>
    T get();

    JSONNode& operator[](int index);
    JSONNode& operator[](const std::string& str);
    JSONNode& operator[](const char* chr);

    static JSONNode parseObject(const std::string& str, int start, int end, std::unordered_map<int, int> &bracePair);
    static JSONNode parseArray(const std::string& str, int start, int end, std::unordered_map<int, int> &bracePair);
    static JSONNode parse(const std::string &str);
    static std::string stringify(const JSONNode& node);
    operator std::string();
    operator int();
    operator double();
    operator bool();
    

private: 
    JSONType m_type{};
    std::unordered_map<std::string, JSONNode> m_data{};
    std::vector<JSONNode> m_array{};
    
    union value{
        std::string m_string;
        double m_number;
        bool m_bool;
        value();
        ~value();

        operator std::string();
        operator double();
        operator bool();
        operator int();

    } m_value;

    void limitToArray();
    void limitToObject();


};

#endif
