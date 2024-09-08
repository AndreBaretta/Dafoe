#ifndef JWT_1533
#define JWT_1533
#define JWT_DISABLE_PICOJSON

#include <jwt-cpp/jwt.h>
#include <jwt-cpp/traits/nlohmann-json/defaults.h>
#include <nlohmann/json.hpp>
#include "Session.hpp"
using json = nlohmann::json;
#include <string>
#include <chrono>
#include <iostream>

class JWToken{
public:
   JWToken(const std::string& secret, const std::string& issuer, const std::chrono::seconds expireTime);
   std::string createToken(const int subject, const bool isAdmin);
   bool validateToken(const std::string& token);
   Session getSession(const std::string& token);

private:
   std::string m_secretKey{};
   std::string m_issuer{};
   std::chrono::seconds m_expireTime{};
};

#endif

