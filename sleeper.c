/* A long running program for testing the CS31 shell program.  It can run with
 * or without a command line argument that specifies how many times the program
 * should sleep for a second before exiting.  With no command line argument it
 * does so 5 times. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   int i, num = 5;

   if(argc == 2) {
      num = atoi(argv[1]);
   }

   for(i = 0; i < num; i++) {
      sleep(1);
   }

   return 0;
}
