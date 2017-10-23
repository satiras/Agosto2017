#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[])
{
    pid_t pid = 0,sid = 0;
    FILE *fp= NULL;
    int i = 0;
    pid = fork();

    if (pid < 0)
    {
        exit(1);
    }

    if (pid > 0)
    {
       printf("pid %d \n", pid);
        exit(0);
    }

    umask(0);

    sid = setsid();
    if(sid < 0)
    {
        exit(1);
    }

      time_t times;
    while (1)
    {

        
        clock_t start;
      
        int w = 0;
        start=clock();
        while(w < 5){
            w = ((clock()-start)/(double)CLOCKS_PER_SEC);
        }
       
        times=time(NULL); 
        fp = fopen ("Log.txt", "w+");
        fprintf(fp, "%s",asctime( localtime(&times) ));
        fclose(fp);
       
    }
    
  
    return (0);
}
