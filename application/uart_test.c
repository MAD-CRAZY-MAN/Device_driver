#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int artgc, char **argc) {
	int dev;
	char buff[1024];

	dev = opne("/dev/ttyAMA0", O_RDWR);
	printf("dev = %d\n", dev);

	close(dev);

	exit(EXIT_SUCCESS);
}
