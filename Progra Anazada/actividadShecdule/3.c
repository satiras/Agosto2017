#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>//sleep
void sing(int senal){
    printf("senal adquirida: %d", senal);
}
int main () {
    signal(SIGINT,sing);
   char str[1000] = "From Edgar Allan Poe: She whom I loved in youth, and of whom I now pen calmly and distinctly these remembrances, was the sole daughter of the only sister of my mother long departed. Eleonora was the name of my cousin. We had always dwelled together, beneath a tropical sun, in the Valley of the Many-Colored Grass. No unguided footstep ever came upon that vale; for it lay away up among a range of giant hills that hung beetling around about it, shutting out the sunlight from its sweetest recesses. No path was trodden in its vicinity; and, to reach our happy home, there was need of putting back, with force, the foliage of many thousands of forest trees, and of crushing to death the glories of many millions of fragrant flowers. Thus it was that we lived all alone, knowing nothing of the world without the valley -- I, and my cousin, and her mother.";
   const char s[2] = " ";
   char *linea;
   linea = strtok(str, s);
   while( linea != NULL ) {
      printf( " %s\n", linea );
      sleep(1);
      linea = strtok(NULL, s);
   }
   return(0);
}