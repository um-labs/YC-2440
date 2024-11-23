#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define LED_ON	0x100001
#define LED_OFF 0x100002

int main(int argc, char *argv[]) {
	int fd;
	int index;

	if (argc != 3) {
		printf("usage:\n $s <on|off> <1|2>\n", argv[0]);
		return -1;
	}

	fd = open("/dev/myled", O_RDWR);
	if (fd < 0) {
		printf("open led failed.\n");
		return -1;
	}
	
	index = strtoul(argv[2], NULL, 0);
	
	if (strcmp(argv[1], "on") == 0)
		ioctl(fd, LED_ON, &index);
	else
		ioctl(fd, LED_OFF, &index);
	close(fd);
	return 0;
}
