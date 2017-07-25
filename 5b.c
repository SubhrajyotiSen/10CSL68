#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv) 
{
	if(argc == 4 && !strcmp(argv[1],"-s") )
			if(symlink(argv[2], argv[3]) == -1)
				printf("Errror found\n");			
			else
				printf("New soft link created\n");			
	else if(argc == 3)
		if(link(argv[1], argv[2]) == -1)
			printf("Errror found\n");
		else
			printf("New hard link created\n");	
	else 
		printf("Error\n");
	return 0;
}