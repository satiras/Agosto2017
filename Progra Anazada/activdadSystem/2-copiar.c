
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
 FILE *fp;
 char filename[100];
 char rengones[100][100];
 char copia[100];
 char ch;
 char cont = 0;
 int numero = 0;
int main( void ) {
    system("ls > archivo.txt");
    system("mkdir back");
     fp = fopen("archivo.txt","r");
   if ( fp )
   {	
    while ((ch=getc(fp)) != EOF) {
           if (ch != '\n') { 
                copia[cont] = ch ;
                cont++;
            }
             if (ch == '\n') {
              strcat(rengones[numero], copia);
                    int y;
                 for(y = 0;y < cont;y++){
                     copia[y] = '\0';
                 }   
                 cont = 0;
                 numero++;
            }
	 }
   }
	
    int x= 0;
    for(x = 0; x < numero; x++){
        char *argv[4] = {"Command-line",rengones[x],"back/", NULL };
	int pid = fork();
	if ( pid == 0 ) {
       
		execvp( "cp",argv );
        _exit(1);
	}
    }

    

	return 0;
}   
