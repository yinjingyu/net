/*
 * =====================================================================================
 *
 *       Filename:  CIpv4Address.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月28日 10时40分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/socket.h>

#include "CIpv4Address.h"


CIpv4Address::CIpv4Address(const char * ipv4Address,in_port_t port)
{
	initialize(ipv4Address,port);
}

CIpv4Address::CIpv4Address(const char* ipv4Address)  // let kernel allocate port
{
	initialize(ipv4Address,0);
}

CIpv4Address::CIpv4Address(in_port_t port) //let kernel allocate ip-address
{
	initialize(0,port);
}
	
CIpv4Address::CIpv4Address() // let kernel allocate ip-address and port
{
	initialize(0,0);
}

void CIpv4Address::initialize(const char * ipv4Address,in_port_t port)
{

	int numericIPv4Addr;

 	bzero(&mSockIpv4Address,sizeof(mSockIpv4Address));


	if(0 == ipv4Address)
		numericIPv4Addr = INADDR_ANY;
	else
		inet_pton(AF_INET,ipv4Address,(void *)&numericIPv4Addr);


 	mSockIpv4Address.sin_family = AF_INET;
	mSockIpv4Address.sin_addr.s_addr = (numericIPv4Addr);
	mSockIpv4Address.sin_port = htons(port);


	mstrIpv4Address = (ipv4Address == 0 ) ? "" : (const_cast<char *>(ipv4Address));
	msPort = port;
	msizeSockLength = sizeof(struct sockaddr_in);
}


string CIpv4Address::getStrIpv4Address()
{
//  debug used to test the value inside the struct of struct sock_addr_in 
	in_addr_t numericIPv4Addr = mSockIpv4Address.sin_addr.s_addr;
	char cIpv4Addr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET,&numericIPv4Addr,cIpv4Addr,INET_ADDRSTRLEN);
	
	return cIpv4Addr;
//	return mstrIpv4Address;
}

in_addr_t CIpv4Address::getSocketIpv4Address()
{
	return mSockIpv4Address.sin_addr.s_addr;
}

short CIpv4Address::getPort()
{
	in_port_t port = ntohs(mSockIpv4Address.sin_port);
	return port;
//	return msPort;
}

in_port_t CIpv4Address::getSocketPort()
{
	return mSockIpv4Address.sin_port;
}

struct sockaddr * CIpv4Address::getSockAddr()
{
	return (struct sockaddr *)&mSockIpv4Address;
}

socklen_t & CIpv4Address::getSockLength()
{
	return msizeSockLength; 
}
