#include "Dexter.h"
#include <errno.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <sstream>
#include <arpa/inet.h>

using namespace std;

Dexter::Dexter(string ip, int port)
{
	// Create socket
	if ((sock_ = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout << "Unable to create socket" << endl;
		throw exception();	// TODO: Use better exception
	}

	cout << sock_ << endl;

	memset(&address_, '0', sizeof(address_));

	address_.sin_family = AF_INET;
	address_.sin_port = htons(port);

	if ((inet_pton(AF_INET, ip.c_str(), &address_.sin_addr)) <= 0)
	{
		cout << "Error processing ip" << endl;
		throw exception();
	}

	int conn_err = connect(sock_, (struct sockaddr *)&address_, sizeof(address_));
	cout << conn_err << endl;
}

void Dexter::move_to_joints(float j1, float j2, float j3, float j4, float j5)
{
	cout << "My Joints" << endl;
	int j1_arc = Dexter::to_arcseconds(j1);
	int j2_arc = Dexter::to_arcseconds(j2);
	int j3_arc = Dexter::to_arcseconds(j3);
	int j4_arc = Dexter::to_arcseconds(j4);
	int j5_arc = Dexter::to_arcseconds(j5);
	cout << "Ahh" << endl;

	std::ostringstream cmd_str;
	cmd_str << "0 0 0 0 a "
			<< j1_arc << " "
			<< j2_arc << " "
			<< j3_arc << " "
			<< j4_arc << " "
			<< j5_arc << " ;";
	cout << "hi" << endl;

	int err;
	try
	{
		cout << "Hmm" << endl;
		err = send(sock_, cmd_str.str().c_str(), cmd_str.str().length(), 0);
		cout << "mmm" << endl;

	}
	catch (int bad)
	{
		cout << "Bad" << endl;
		cout << bad << endl;
	}

	cout << "there" << endl;

	cout << err << endl;
	cout << cmd_str.str() << endl;



}

int Dexter::to_arcseconds(float degrees) {
	return (int)(degrees * 3600);
}