#include "Dexter.h"
#include <unistd.h>

int main(int argc, char const *argv[]) {

	Dexter d("192.168.1.240", 50000);

	// for (int i = 0; i < 50; i++)
	// {
	// 	d.move_to_joints(36, 0, 15, 0, -30);
	// 	usleep(2000000);
	// 	d.move_to_joints(0, 0, 0, 0, 0);
	// 	usleep(2000000);
	// }

	d.move_to_joints({36, 0, 15, 0, -30});
	d.move_to_joints({0, 0, 0, 0, 0});
	d.move_to_joints({36, 0, 15, 0, -30});
	d.move_to_joints({0, 0, 0, 0, 0});

	return 0;
}