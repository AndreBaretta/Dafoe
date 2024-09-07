#define JWT_DISABLE_PICOJSON

#include <jwt-cpp/jwt.h>
#include <jwt-cpp/traits/nlohmann-json/defaults.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <string>
#include <chrono>
#include <iostream>

class JWToken{
public:
   JWToken(const std::string& secret, const std::string& issuer);
   std::string createToken(const int subject, const bool isAdmin, const std::chrono::seconds expiresIn);
   bool validateToken(std::string& token);

private:
   std::string m_secretKey{};
   std::string m_issuer{};
};



