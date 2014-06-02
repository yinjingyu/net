/*
 * =====================================================================================
 *
 *       Filename:  CSocket.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月28日 22时01分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>
#include <errno.h>  // errorno
#include <unistd.h> //read/write

#include "IAddress.h"
#include "CIpv4Address.h"
#include "CSocket.h"

#include <string.h>
#include <iostream>


using namespace std;

/*客户端socket 不需要指定地址和端口号*/
CSocket::CSocket(int addressFamily,int socketType,const char * ip,in_port_t port)
{
	
	miSockfd = socket(addressFamily,socketType,0);	 	 	

	if(miSockfd < 0 )
	{
		throw "socket() failed in CSocket::CSocket";	
	}

 	if(addressFamily == AF_INET)
		mptrIAddress = new CIpv4Address(ip,port);
	else
	{
		/* do nothing */
		throw "we cannot process this protocol now!";
	}
}

CSocket::~CSocket()
{
	if(mptrIAddress == 0)
	{
		 delete mptrIAddress;
		 mptrIAddress = 0;
	}
}

	//返回代表服务器的描述符
int CSocket::connectToServer()
{
	int ret = -1;
	ret = connect(miSockfd,mptrIAddress->getSockAddr(),mptrIAddress->getSockLength()); 
	if(ret < 0)
	{
		delete this;
		throw "connect failed , this socket will be destroyed, please rebuild a socket";
	}
	
	return ret;
}


	
int CSocket::bindSocket()
{

	int ret = bind(miSockfd,mptrIAddress->getSockAddr(),mptrIAddress->getSockLength()); 	 			

	if(ret < 0)
	{
		cout << strerror(errno)<< endl;
		CIpv4Address * pip = (CIpv4Address *)mptrIAddress;
		cout << pip->getStrIpv4Address() << endl;
	}
	return ret;

}

int CSocket::listenSocket()
{
	return listen(miSockfd,SOMAXCONN);	
}

	//pAddress 必须指向是有效的内存空间
	//如果accept成功则返回值代表了客户端的描述符
int CSocket::acceptClient(IAddress * pAddress)
{
	if(0 == pAddress)
	{
		throw "error in CSocket::acceptClient::pAddress is not a valid memory space";
	}

//	struct sockaddr_in ip;
//	socklen_t len = sizeof(struct sockaddr_in);
	return accept(miSockfd,pAddress->getSockAddr(),&pAddress->getSockLength());
//	int ret = accept(miSockfd,pAddress->getSockAddr(),&len);
//	int ret = accept(miSockfd,(struct sockaddr *)&ip,&len);

//	cout << "in CSocket , the accepted ip is " << ip.sin_addr.s_addr << endl;
	
//	struct sockaddr_in * pip4 ;
//	struct sockaddr * r = pAddress->getSockAddr();
//	pip4 = (struct sockaddr_in *)r;
//
//	cout << "in CSocket , the accepted ip is " << pip4->sin_addr.s_addr << endl;
	
//	CIpv4Address * pip4 = (CIpv4Address *)pAddress;
//	cout << "the ip is " << pAddress->getStrIpv4Address()  <<endl;
//
//	return ret;
}

ssize_t CSocket::readn(int sockfd,void * datas, size_t n)
{
	size_t nleft = n;
	ssize_t nreaded;
	char * cursor = (char *)datas;	
	while(nleft > 0)
	{
//		if( (nreaded = read(miSockfd,cursor,nleft)) < 0)
		if( (nreaded = read(sockfd,cursor,nleft)) < 0)
		{
			if(errno == EINTR)
				nreaded = 0;
			else
			{
				cout << "In CSocket::readn : " <<strerror(errno)<< endl;
				return -1;
			}
		}
		else if(nreaded == 0)	
		{
			break;
		}
		nleft -= nreaded;
		cursor += nreaded;
	}
	
	return (n - nleft); //对方发送的可能比要求接收的少，所以返回值可能小于预期接收的n
}

ssize_t CSocket::writen(int sockfd,const void * datas, size_t n)
{
	size_t nleft = n;
	ssize_t nwrited = 0;
	char * cursor = (char *)datas;

	while(nleft > 0)
	{
		if( (nwrited = write(sockfd,cursor,nleft)) < 0)
		{
			if(errno == EINTR)
				nwrited = 0;	
			else 
				return -1;
		}
		nleft -= nwrited;
		cursor += nwrited;
	}
	
	//如果不出现异常则保证发送n个字节出去
	return n;
}
	
int CSocket::closeSocket()
{
	return close(miSockfd);
}

int CSocket::getSockFd()
{
	return miSockfd;
}
