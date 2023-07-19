#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd = open("./main.c", O_RDONLY);
	close(fd);
	printf("fd: %d", fd);
}