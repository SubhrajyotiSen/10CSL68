#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
	if (argc !=2 && argc != 3) {
		cout << "Usage " << argv[0] << "<file>[<args>]" << endl;
		return 0;
	}
	int fd;
	char buf[256];
	(void) mkfifo(argv[1], S_IFIFO | S_IRWXU | S_IRWXG | S_IRWXO);
	if (argc == 2) {
		fd = open(argv[1], O_RDONLY);
		while(read(fd, buf, sizeof(buf)) > 0)
			cout << buf << endl;
	}
	else {
		fd = open(argv[1], O_WRONLY);
		write(fd, argv[2], strlen(argv[2]));
	}
	close(fd);
	return 0;
}