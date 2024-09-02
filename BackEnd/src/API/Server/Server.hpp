#ifndef SERVER_2208
#define SERVER_2208
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include <openssl/opensslv.h>

class Server{
public:
   Server(std::string ipAddress, int port, bool TLS = 0);
   ~Server();
   int startListen();
   int acceptConnection();
   std::string readRequest();
   int writeResponse();
   void setBSize(int bSize);
   void setResponse(std::string response);
   void createContext();
   void configureContext();

private:
   int m_port{};
   int m_socket{};
   int m_newSocket{};
   int m_bufferSize{1024};
   uint m_socketAddressSize{};
   int64_t m_incomingMessage{};
   std::string m_ipAddress{};
   sockaddr_in m_socketAddress{};
   std::string m_serverMessage{};
   SSL_CTX* m_context{};
   SSL* m_ssl{};
   bool m_tls{};
   int startServer();
   void closeServer();
};


#endif
