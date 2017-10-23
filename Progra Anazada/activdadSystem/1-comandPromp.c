#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
      char c1[50];
      char c2[14];
      //int system(const char *command);
    printf("dame el comando 1\n");
	scanf("%s", c1);
    printf("dame el comando 2\n");
	scanf("%s", c2);
    strcat(c1, " ");
    strcat(c1,c2);
	
    printf("%s",&c1);
        
    
    system(c1);
        //system(c2);
        return 0;
}
