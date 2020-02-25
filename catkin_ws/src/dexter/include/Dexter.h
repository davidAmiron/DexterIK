#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

class Dexter
{

public:
	Dexter(std::string ip, int port);
	~Dexter();

	void move_to_joints(float j1, float j2, float j3, float j4, float j5);


private:
	struct sockaddr_in address_;
	int sock_;

	int to_arcseconds(float degrees);
	

};