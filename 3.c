#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv) {
	int fd;
	char buffer[255];
	struct flock fvar;
	if (argc != 2) {
		printf("Incorrect number of arguements\n");
		return 1;
	}
	if ((fd = open(argv[1], O_RDWR)) == -1) {
		printf("Error\n");
		return 1;
	}
	fvar.l_type = F_WRLCK;
	fvar.l_whence = SEEK_END;
	fvar.l_start = SEEK_END - 100;
	fvar.l_len = 100;
	if (fcntl(fd, F_GETLK, &fvar) == -1) {
		printf("File locked by process (pid): \t %d\n", fvar.l_pid);
		return 1;
	}
	else {
		if ((fcntl(fd, F_SETLK, &fvar)) == -1)
			printf("Failed to set lock\n");
		if ((lseek(fd, SEEK_END - 50, SEEK_END)) == -1)
			return 1;
		if ((read(fd, buffer, 100)) == -1)
			return 1;
		puts(buffer);
	}
	fvar.l_type = F_UNLCK;
	fvar.l_whence = SEEK_SET;
	fvar.l_start = 0;
	fvar.l_len = 0;
	if ((fcntl(fd, F_UNLCK, &fvar)) == -1) {
		printf("Unable to unlock file\n");
		return 1;
	}
	close(fd);
	return 0;
}