/*
 * =====================================================================================
 *
 *       Filename:  CIpv4AddressTest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月28日 10时46分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <limits.h>
#include "gtest/gtest.h"
#include "../CIpv4Address.h"
#include <string>
#include <sys/socket.h>

TEST(CIpv4AddressTestSuit,twoArgCtrTest)
{
	CIpv4Address * ipv4 = new CIpv4Address("192.168.1.100",8080);
	
	EXPECT_STREQ("192.168.1.100",ipv4->getStrIpv4Address().c_str());

	EXPECT_EQ(8080,ipv4->getPort());
//	EXPECT_EQ(8080,ipv4->getSocketPort());
}

TEST(CIpv4AddressTestSuit,oneArgCtrTest)
{
	CIpv4Address * ipv4 = new CIpv4Address(8080);
	EXPECT_EQ(0,ipv4->getSocketIpv4Address());
	EXPECT_EQ(8080,ipv4->getPort());

	CIpv4Address * ipv4_  = new CIpv4Address("192.168.1.100");
	EXPECT_STREQ("192.168.1.100",ipv4_->getStrIpv4Address().c_str());
	EXPECT_EQ(0,ipv4_->getPort());
}

TEST(CIpv4AddressTestSuit,noArgCtrTest)
{
	CIpv4Address * ipv4 = new CIpv4Address();
	EXPECT_EQ(0,ipv4->getSocketIpv4Address()) << "some thing wrong happend!";
	EXPECT_EQ(0,ipv4->getPort());
}

TEST(CIpv4AddressTestSuit,sockaddrTest)
{
	CIpv4Address * ipv4 = new CIpv4Address("192.168.1.100",8080);
	struct sockaddr * pSock = ipv4->getSockAddr();
	EXPECT_EQ(AF_INET,pSock->sa_family);	
	EXPECT_EQ(INET_ADDRSTRLEN,ipv4->getSockLength());
}


