#include "Dexter.h"

int main(int argc, char const *argv[]) {

	Dexter d("127.0.0.1", 50000);
	d.move_to_joints(1.57, 0, 0, 0, 0);
	return 0;
}