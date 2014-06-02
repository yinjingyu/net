#ifndef IADDRESS_H
#define IADDRESS_H

#include <sys/socket.h>

class IAddress
{
public:
	virtual struct sockaddr * getSockAddr() = 0;
	virtual socklen_t &  getSockLength() = 0;
};

#endif
