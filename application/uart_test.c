#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <sys/ioctl.h>
#include <sys/poll.h>

#include <termios.h>

void close_serial(int fd);
int open_serial(char *dev_name, int baud, int vtime, int vmin);
void write_str();
void read_str();

int main(int argc, char **argv) {
	int fd;
	int baud;
	char dev_name[128];
	char cc, buf[128];
	int rdcnt;

	if (argc != 3)
	{	
		printf("usage: ./uart_test [device name] [baud rate]");
		return -1;
	}
	
	strcpy(dev_name, argv[1]);
	baud = strtoul(argv[2], NULL, 10);

	fd = open_serial(dev_name, baud, 10, 32);

	for (cc='A';cc<='z'; cc++)
	{
		memset(buf, cc, 32);
		write(fd, buf, 32);

		rdcnt = read(fd, buf, sizeof(buf));
		if(rdcnt>0)
		{
			buf[rdcnt] = '\0';
			printf("<%s rd = %2d>%s\n", dev_name, rdcnt, buf);
		}
		sleep(1);
	}

	close_serial(fd);

	printf("serial test end\n");
	return 0;
}
		
int open_serial(char *dev_name, int baud, int vtime, int vmin)
{
	int fd;
	struct termios newtio;

	fd = open(dev_name, O_RDWR | O_NOCTTY); //O_NOCTTY: ctrl-c cant control terminal
	if(fd<0)
	{
		printf("Device OPEN FAIL %s\n", dev_name);
		return -1;
	}

	memset(&newtio, 0, sizeof(newtio));
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;

	newtio.c_cflag = CS8 | CLOCAL | CREAD;//CS8(data bit): 8bit

	switch(baud)
	{
		case 115200:newtio.c_cflag |= B115200;	break;
		case 9600:newtio.c_cflag |= B9600; break;
	}

	newtio.c_lflag = 0;
	newtio.c_cc[VTIME] = vtime;
	newtio.c_cc[VMIN] = vmin;

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &newtio);

	return fd;
}

void close_serial(int fd)
{
	close(fd);
}
