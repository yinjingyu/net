#ifndef CSOCKET_H
#define CSOCKET_H


#include <netinet/in.h>
#include "IAddress.h"

class CSocket
{
public:
	/*客户端socket 不需要指定地址和端口号*/
	CSocket(int addressFamily,int socketType,const char * ip,in_port_t port);
	~CSocket();

	//返回代表服务器的描述符
	int connectToServer();

	
	int bindSocket();
	int listenSocket();

	//pAddress 必须指向是有效的内存空间
	//如果accept成功则返回值代表了客户端的描述符
	int acceptClient(IAddress * pAddress);

	ssize_t readn(int sockfd,void * datas, size_t n);
	ssize_t writen(int sockfd,const void * datas, size_t n);

	int closeSocket();
	int getSockFd();

private:
	int miSockfd;

	IAddress * mptrIAddress;
};


#endif
