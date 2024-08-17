#ifndef TCPSERVER_2208
#define TCPSERVER_2208
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include "HTTPRequestParser.hpp"

class TCPServer{
   public:
      TCPServer(std::string ipAddress, int port);
      ~TCPServer();
      int startListen();
      int acceptConnection();
      int readRequest();
      int writeResponse();
      void setBSize(int bSize);
      void setResponse(std::string response);

   private:
      HTTPRequestParser m_HTTPRParser;
      int m_port{};
      int m_socket{};
      int m_newSocket{};
      int m_bufferSize{1024};
      uint m_socketAddressSize{};
      int64_t m_incomingMessage{};
      std::string m_ipAddress{};
      sockaddr_in m_socketAddress{};
      std::string m_serverMessage{};
      int startServer();
      void closeServer();
};


#endif
