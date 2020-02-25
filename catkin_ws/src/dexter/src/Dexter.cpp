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

void Dexter::move_to_joints(float j1, float j2, float j3, float j4, float j5)
{
	int j1_arc = Dexter::to_arcseconds(j1);
	int j2_arc = Dexter::to_arcseconds(j2);
	int j3_arc = Dexter::to_arcseconds(j3);
	int j4_arc = Dexter::to_arcseconds(j4);
	int j5_arc = Dexter::to_arcseconds(j5);

	std::ostringstream cmd_str;
	cmd_str << "0 0 0 0 a "
			<< j1_arc << " "
			<< j2_arc << " "
			<< j3_arc << " "
			<< j4_arc << " "
			<< j5_arc << " ;";

	send(sock_, cmd_str.str().c_str(), cmd_str.str().length(), 0);

	// Maybe send F opcode to make sure command is sent

	char buffer[1024];
	bzero(buffer, 1024);

	int readret = read(sock_, buffer, 1024);
	string value(buffer, readret);
	cout << "Read ret: " << readret << endl;
	cout << value << endl;
	//printf("%s", buffer);

	// TODO: Figure out how to read data

}

int Dexter::to_arcseconds(float degrees) {
	return (int)(degrees * 3600);
}