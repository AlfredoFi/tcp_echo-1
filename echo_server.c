#include <stdio.h>   
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>         //llamado de librerias requeridas

void handleTCPEchoClient(int clientSocket){ // se crea el socket
  char buffer[BUFSIZ];         //after opening a stream you can explicitly specify what kind of buffering you want it to have.
  ssize_t bytesRcvd = recv(clientSocket, buffer, BUFSIZ, 0);  //configuración de parametros para rebir frames 
  send(clientSocket, buffer, bytesRcvd, 0);  // configuración de parametros para enviar frames
  close(clientSocket); // Una vez terminado el proceso el socket debe de cerrarse. 
}

void handleTimeClient(){}   //función encarda del tiempo del cliente.

int main(){
  int serverSocket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);    // declaración del socket ip, numero de socket y protocolo
  struct sockaddr_in6 serverAddress; 
  memset(&serverAddress, 0, sizeof(serverAddress)); // función memeset copia el valor para asignarlo al server Address  
  serverAddress.sin6_family = AF_INET6; //crea un nuevo socket
  serverAddress.sin6_addr = in6addr_any; 
  serverAddress.sin6_port = htons(5000); // asiganción del puerto al socket
  bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)); // función bind para que el socket no se mueva de manera aleatoria y quede fijo el valor
  if(listen(serverSocket, SOMAXCONN) < 0)  //escuha del socket
    exit(5);
  for(;;){              //proceso del socket para escuhar, aceptar la conexión
    struct sockaddr_in clientAddress;
    socklen_t clientAddrLen = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddrLen );    
    if(clientSocket < 0)
      exit(5);
    char clientIp[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddress.sin_addr.s_addr, clientIp, sizeof(clientIp));
    printf("%s %d\n", clientIp, ntohs(clientAddress.sin_port));
    handleTCPEchoClient(clientSocket);
  }
  return 0;
}
