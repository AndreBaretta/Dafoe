#include "TCPServer.hpp"
#include <unistd.h>
#include <iostream>
#include <cstring>

TCPServer::TCPServer(std::string ipAddress, int port)
: m_ipAddress{ipAddress}
, m_port{port}
{
   this->startServer();
}

TCPServer::~TCPServer(){
   close(this->m_socket);
   close(this->m_newSocket);
}

int TCPServer::startServer(){
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

void TCPServer::closeServer(){
   shutdown(this->m_socket,SHUT_RDWR);
   shutdown(this->m_newSocket,SHUT_RDWR);
}

int TCPServer::startListen(){
   if(listen(this->m_socket, 5) < 0){
      std::cout << "Erro ao escutar o socket.\n";
      return -1;
   }
   std::cout << "Escutando o endereço: " << inet_ntoa(m_socketAddress.sin_addr) << "; porta: " << ntohs(m_socketAddress.sin_port) << "\n";
   return 0;
}

int TCPServer::acceptConnection(){
   this->m_newSocket = accept(this->m_socket, (sockaddr*)&this->m_socketAddress, (socklen_t*)&this->m_socketAddressSize);
   if(this->m_newSocket < 0){
      std::cout << "Erro ao aceitar conexão do ip: " << inet_ntoa(m_socketAddress.sin_addr) <<
         "; porta: " << ntohs(m_socketAddress.sin_port) << "\n";
      return -1;
   }
   return 0;
}

bool TCPServer::readRequest(std::string* request){
   char buffer[this->m_bufferSize];
   ssize_t bytesReceived = read(this->m_newSocket, buffer, this->m_bufferSize);
   if(bytesReceived < 0){
      return false;
   }
   std::string stringBuffer(buffer);
   *request = stringBuffer;
   return true;
}

int TCPServer::writeResponse(){
   long bytesSent = write(this->m_newSocket, this->m_serverMessage.c_str(), this->m_serverMessage.size());
   if(bytesSent == m_serverMessage.size()){
      std::cout << "Mensagem enviada ao cliente.\n";
      close(m_newSocket);
      return 0;
   }
   std::cout << "Erro enviando resposta para o cliente.\n";
   close(m_newSocket);
   return -1;
}

void TCPServer::setBSize(int bSize){
   this->m_bufferSize = bSize;
}

void TCPServer::setResponse(std::string response){
   this->m_serverMessage = response;
}


