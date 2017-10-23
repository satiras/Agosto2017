#include <stdio.h>
int main() {
	int inicio = fork();
	if ( inicio == 0 ) {
		printf( "nino\n" );
	} else {
		printf( "Id %d\n", inicio );
	}
	return 0;
}
