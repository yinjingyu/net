#ifndef CIPV4ADDRESS_H
#define CIPV4ADDRESS_H

#include <netinet/in.h>
#include <string>
#include "IAddress.h"

using namespace std;


class IAddress;

class CIpv4Address : public IAddress
{

public:
	CIpv4Address(const char * ipv4Address,in_port_t port);

	CIpv4Address(const char * ipv4Address);// let kernel allocate port

	CIpv4Address(in_port_t port);//let kernel allocate ip-address

	CIpv4Address(); // let kernel allocate ip-address and port

	string getStrIpv4Address();

	in_addr_t getSocketIpv4Address();

	short getPort();

 	in_port_t getSocketPort();

	virtual struct sockaddr * getSockAddr();
	virtual socklen_t & getSockLength();
private:

	void initialize(const char * ipv4Address,in_port_t port);

	struct sockaddr_in mSockIpv4Address;
	string mstrIpv4Address;
	short  msPort;
    socklen_t msizeSockLength;
};

#endif
