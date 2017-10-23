#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main( void ) {
	char *argv[3] = {"linea", ".", NULL };

	int algo = fork();

	if ( algo == 0 ) {
		execvp( "find",argv );
	}
	return 0;
}   
