#include "Dexter.h"
#include <errno.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <sstream>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

Dexter::Dexter(string ip, int port)
{
	// Create socket
	if ((sock_ = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout << "Unable to create socket" << endl;
		throw exception();	// TODO: Use better exception
	}

	memset(&address_, '0', sizeof(address_));

	address_.sin_family = AF_INET;
	address_.sin_port = htons(port);

	if ((inet_pton(AF_INET, ip.c_str(), &address_.sin_addr)) <= 0)
	{
		cout << "Error processing ip" << endl;
		throw exception();
	}

	int conn_err = connect(sock_, (struct sockaddr *)&address_, sizeof(address_));
}

Dexter::~Dexter()
{
	close(sock_);
}

// Joints in radians
void Dexter::move_to_joints(std::vector<float> joints)
{
	int j1_arc = Dexter::to_arcseconds(joints[0]);
	int j2_arc = Dexter::to_arcseconds(joints[1]);
	int j3_arc = Dexter::to_arcseconds(joints[2]);
	int j4_arc = Dexter::to_arcseconds(joints[3]);
	int j5_arc = Dexter::to_arcseconds(joints[4]);


	std::ostringstream cmd_str;
	cmd_str << "0 0 0 0 a "
			<< j1_arc << " "
			<< j2_arc << " "
			<< j3_arc << " "
			<< j4_arc << " "
			<< j5_arc << " ;";

	cout << "Sending Values: " << cmd_str.str() << endl;
	send(sock_, cmd_str.str().c_str(), cmd_str.str().length(), 0);

	// Maybe send F opcode to make sure command is sent

	// char buffer[1024];
	// bzero(buffer, 1024);

	// int readret = read(sock_, buffer, 1024);
	// string value(buffer, readret);
	// cout << "Read ret: " << readret << endl;
	// cout << value << endl;
	//printf("%s", buffer);

	// TODO: Figure out how to read data

}

int Dexter::to_arcseconds(float radians) {
	return (int)(radians * (180 / 3.14159265) * 3600);
}