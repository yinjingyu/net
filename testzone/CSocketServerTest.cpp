/*
 * =====================================================================================
 *
 *       Filename:  CSocketTest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月28日 22时15分00秒
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
#include <string.h>
#include <sys/socket.h>
#include "../CSocket.h"
#include <unistd.h>

using namespace std;

TEST(CSocketServerTestSuit,newSocketTest)
{
	CIpv4Address clientAddress;
	int client;
	char data[20];

	CSocket socket(AF_INET,SOCK_STREAM,"127.0.0.1",8765);

	EXPECT_EQ(0,socket.bindSocket());
	EXPECT_EQ(0,socket.listenSocket());

	//从客户端接收数据
	client = socket.acceptClient(&clientAddress);
	socket.readn(client,data,20);
	EXPECT_STREQ("hello",data);

	//向客户端发送数据
	bzero(data,20);
	strcpy(data,"hello 你妹");
	socket.writen(client,data,20);
	
	EXPECT_EQ(0,socket.closeSocket());
}
