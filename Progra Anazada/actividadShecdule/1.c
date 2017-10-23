
//prubea1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/resource.h>
int main( void ) {
  
    int which = PRIO_PROCESS;
    id_t pid;
    int set;
    int get;
    int priority[5];
     priority[0] = 1;
     priority[1] = 15;
     priority[2] = 11;
     priority[3] = 3;
     priority[4] = 8;
    int x;
for(x = 0; x < 5; x++){
        
	 pid = fork();
	if ( pid == 0 ) {
        set = setpriority(which, getpid(), priority[x]);
        get = getpriority(which, getpid());
       printf("Child: my pid is: %d, and my priority is: %d\n",getpid(),get);
       exit(0);
		
	}
    }

    

	return 0;
}   
