#include "JWToken.hpp"

JWToken::JWToken(const std::string& secret, const std::string& issuer)
: m_secretKey{secret}
, m_issuer{issuer}
{}

std::string JWToken::createToken(const int subject, const bool isAdmin, const std::chrono::seconds expiresIn){
   auto now = std::chrono::system_clock::now();
   auto expiresAt = now + expiresIn;
   auto token = jwt::create()
                .set_type("JWT")
                .set_issuer(this->m_issuer)
                .set_subject(std::to_string(subject))
                .set_payload_claim("admin", jwt::claim(isAdmin))
                .set_issued_now()
                .set_expires_in(expiresIn)
                .sign(jwt::algorithm::hs256(this->m_secretKey));
   return token;
}

bool JWToken::validateToken(std::string& token){
   try {
      auto decoded_token = jwt::decode(token);
      auto verifier = jwt::verify()
         .allow_algorithm(jwt::algorithm::hs256{this->m_secretKey})
         .with_issuer(this->m_issuer);            

      verifier.verify(decoded_token);

      auto exp_claim = decoded_token.get_expires_at();
      if (std::chrono::system_clock::now() > exp_claim) {
         return false;
      }
      return true;

   } catch (const std::exception& e) {
      std::cerr << "Erro ao validar o token: " << e.what() << std::endl;
      return false;
   }

}






