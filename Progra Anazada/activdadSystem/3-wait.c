#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
 
int main()
{
    if (fork()== 0)
        printf("nino\n");
    else
    {
        printf("papa\n");
        wait(NULL);
        printf("se murio el nino\n");
    }
 
    printf("Bye\n");
    return 0;
}
