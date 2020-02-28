#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>

class Dexter
{

public:
	Dexter(std::string ip, int port);
	~Dexter();

	void move_to_joints(std::vector<float> joints);


private:
	struct sockaddr_in address_;
	int sock_;

	int to_arcseconds(float degrees);
	

};