#include "JWToken.hpp"

JWToken::JWToken(const std::string& secret, const std::string& issuer, const std::chrono::seconds expireTime)
: m_secretKey{secret}
, m_issuer{issuer}
, m_expireTime{expireTime}
{}

std::string JWToken::createToken(const int subject, const bool isAdmin){
   auto now = std::chrono::system_clock::now();
   auto token = jwt::create()
                .set_type("JWT")
                .set_issuer(this->m_issuer)
                .set_subject(std::to_string(subject))
                .set_payload_claim("admin", jwt::claim(isAdmin))
                .set_issued_now()
                .set_expires_in(this->m_expireTime)
                .sign(jwt::algorithm::hs256(this->m_secretKey));
   return token;
}

bool JWToken::validateToken(const std::string& token){
   try {
      auto auxToken = token.substr(0,token.size()-1);
      auto decodedToken = jwt::decode(auxToken);
      auto verifier = jwt::verify()
         .allow_algorithm(jwt::algorithm::hs256{this->m_secretKey})
         .with_issuer(this->m_issuer);            

      verifier.verify(decodedToken);

      auto expClaim = decodedToken.get_expires_at();
      if (std::chrono::system_clock::now() > expClaim) {
         return false;
      }
      return true;

   } catch (const std::exception& e) {
      std::cerr << "Erro ao validar o token: " << e.what() << '\n';
      return false;
   }
}

Session JWToken::getSession(const std::string& token){
   try {
      auto auxToken = token.substr(0,token.size()-1);
      auto decodedToken = jwt::decode(auxToken);
      auto verifier = jwt::verify()
                      .allow_algorithm(jwt::algorithm::hs256{this->m_secretKey})
                      .with_issuer(this->m_issuer);

      verifier.verify(decodedToken);

      int id = std::stoi(decodedToken.get_subject());
      bool admin = decodedToken.get_payload_claim("admin").as_boolean();
      Session session = Session(id,admin);
      return session;
   } catch(std::exception &e){
      std::cerr << "Erro ao validar o Token: " << e.what() << '\n';
      throw;
   }
}







