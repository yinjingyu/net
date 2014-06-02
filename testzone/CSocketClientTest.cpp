/*
 * =====================================================================================
 *
 *       Filename:  CSocketClientTest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月29日 09时54分23秒
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
#include "../CSocket.h"

#include <string.h>

using namespace std;

TEST(CSocketClientTestSuit,newSocketTest)
{

	char data[20];
	CSocket socket(AF_INET,SOCK_STREAM,"127.0.0.1",8765);

	EXPECT_EQ(0,socket.connectToServer());

	//向服务器发送数据
	strcpy(data,"hello");
	socket.writen(socket.getSockFd(),data,20);

	//从服务器接收数据
	bzero(data,20);
	socket.readn(socket.getSockFd(),data,20);	
	
	EXPECT_STREQ("hello 你妹",data);
	EXPECT_EQ(0,socket.closeSocket());
}
