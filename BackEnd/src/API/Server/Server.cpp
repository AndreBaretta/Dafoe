#include "Server.hpp"
#include <unistd.h>
#include <iostream>
#include <cstring>

Server::Server(std::string ipAddress, int port, bool TLS)
: m_ipAddress{ipAddress}
, m_port{port}
, m_tls{TLS}
{
   this->startServer();
   this->createContext();
   this->configureContext();
}

Server::~Server(){
   close(this->m_socket);
   close(this->m_newSocket);
   if(this->m_tls)
      SSL_CTX_free(this->m_context);
}

int Server::startServer(){
   this->m_socket = socket(AF_INET, SOCK_STREAM, 0);
   this->m_socketAddress.sin_family = AF_INET;
   this->m_socketAddress.sin_port = htons(this->m_port);
   this->m_socketAddress.sin_addr.s_addr = inet_addr(this->m_ipAddress.c_str());
   this->m_socketAddressSize = sizeof(this->m_socketAddress);

   if(bind(this->m_socket, (sockaddr*)&this->m_socketAddress, this->m_socketAddressSize) < 0){
      std::cout << "Erro ao se conectar com o endereço.\n";
      return -1;
   }
   if(this->m_socket < 0){
      std::cout << "Erro ao criar o socket.\n";
      return -1;
   }
   return 0;
}

void Server::closeServer(){
   shutdown(this->m_socket,SHUT_RDWR);
   shutdown(this->m_newSocket,SHUT_RDWR);
}

int Server::startListen(){
   if(listen(this->m_socket, 20) < 0){
      std::cout << "Erro ao escutar o socket.\n";
      return -1;
   }
   std::cout << "Escutando o endereço: " << inet_ntoa(m_socketAddress.sin_addr) << "; porta: " << ntohs(m_socketAddress.sin_port) << "\n";
   return 0;
}

int Server::acceptConnection(){
   this->m_newSocket = accept(this->m_socket, (sockaddr*)&this->m_socketAddress, (socklen_t*)&this->m_socketAddressSize);
   if(this->m_newSocket < 0){
      std::cout << "Erro ao aceitar conexão do ip: " << inet_ntoa(m_socketAddress.sin_addr) <<
         "; porta: " << ntohs(m_socketAddress.sin_port) << "\n";
      return -1;
   }
   if(this->m_tls){
      this->m_ssl = SSL_new(this->m_context);
      SSL_set_fd(this->m_ssl, this->m_newSocket);
      int ret = SSL_accept(this->m_ssl);
      if(ret <= 0){
         int error = SSL_get_error(m_ssl, ret);
         ERR_print_errors_fp(stderr);
         SSL_shutdown(this->m_ssl);
         SSL_free(this->m_ssl);
         close(this->m_newSocket);
         return -1;
      }
   }
   return 0;
}

std::string Server::readRequest(){
   std::string request{};
   char buffer[this->m_bufferSize];
   if(!this->m_tls){
      ssize_t bytesReceived = read(this->m_newSocket, buffer, this->m_bufferSize);
      if(bytesReceived < 0){
         return request;
      }
   }else{
      SSL_read(this->m_ssl, buffer, this->m_bufferSize);
   }
   std::string stringBuffer = buffer;
   request = stringBuffer;
   return request;
}

int Server::writeResponse(){
   if(!this->m_tls){
      long bytesSent = write(this->m_newSocket, this->m_serverMessage.c_str(), this->m_serverMessage.size());
      if(bytesSent == this->m_serverMessage.size()){
         std::cout << "Mensagem enviada ao cliente.\n";
         close(this->m_newSocket);
         return 0;
      }
      std::cerr << "Erro ao enviar mensagem ao cliente" << '\n';
      return -1;
   }
   SSL_write(this->m_ssl, this->m_serverMessage.c_str(), this->m_serverMessage.size());
   SSL_shutdown(this->m_ssl);
   SSL_free(this->m_ssl);
   close(this->m_newSocket);
   return 0;
}

void Server::setBSize(int bSize){
   this->m_bufferSize = bSize;
}

void Server::setResponse(std::string response){
   this->m_serverMessage = response;
}

void Server::createContext(){
   if(!this->m_tls)
      return;
   this->m_context = SSL_CTX_new(TLS_server_method());
   if(!this->m_context){
      perror("Erro ao criar contexto SSL");
      ERR_print_errors_fp(stderr);
      exit(EXIT_FAILURE);
   }
}

void Server::configureContext(){
   if(!this->m_tls)
      return;
   if(SSL_CTX_use_certificate_file(this->m_context, CERT_PATH, SSL_FILETYPE_PEM) <= 0){
      ERR_print_errors_fp(stderr);
      exit(EXIT_FAILURE);
   }
   if(SSL_CTX_use_PrivateKey_file(this->m_context, KEY_PATH, SSL_FILETYPE_PEM) <= 0){
      ERR_print_errors_fp(stderr);
      exit(EXIT_FAILURE);
   }
}

