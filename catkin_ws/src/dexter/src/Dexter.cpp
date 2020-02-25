#include "Dexter.h"
#include <string.h>
#include <sys/socket.h>
#include <errno.h>

Dexter::Dexter(std::string ip, int port)
{
	// Create socket
	if ((sock_ = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout << "Unable to create socket" << endl;
		return -1;
	}

	memset(&address_, '0', sizeof(address_));

	address_.sin_family = AF_INET;
	address_.sin_port = htons(port);

	if ((inet_pton(AF_INET, ip.c_str(), address_.sin_addr)) <= 0)
	{
		cout << "Error processing ip" << endl;
		return -1;
	}
}

void Dexter::move_to_joints(float j1, float j2, float j3, float j4, float j5)
{
	j1_arc = to_arcseconds(j1);
	j2_arc = to_arcseconds(j2);
	j3_arc = to_arcseconds(j3);
	j4_arc = to_arcseconds(j4);
	j5_arc = to_arcseconds(j5);

	std::osstringstream cmd_str;
	cmd_str << "0 0 0 0 a "
			<< j1_arc << " "
			<< j2_arc << " "
			<< j3_arc << " "
			<< j4_arc << " "
			<< j5_arc << " ;";

	err = send(sock_, cmd_str.c_str(), strlen(cmd_str.c_str()), 0);



}

int to_arcseconds(float degrees) {
	return (int)(degrees * 3600);
}