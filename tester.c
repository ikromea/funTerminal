#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "parsecmd.h"

/* static: means these functions cannot be called from outside this file */
static void print_cmd_args(char *cmdline, char **argv );
static void print_bg(int bg) ;

int main(int argc, char **argv) {

    int bg;
    char cmdline[MAXLINE];
    char **args;

    printf("Type \"quit\" to stop.\n");
    while(1) {
        /* Print the shell prompt */
        printf("enter a cmd line> ");
        fflush(stdout);

        /* Read in the next command. */
        if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin)) {
            perror("fgets error");
        }

        /* Check for end of file (ctrl-d). */
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            exit(0);
        }

        /* Quit if we're told to do so. */
        if (!strcmp(cmdline, "quit\n")) {
            fflush(stdout);
            exit(0);
        }

        /* Initialize bg to zero in case your parse_cmd_dynamic implementation
         * errantly fails to set it. */
        bg = 0;

        /* Call your parser. */
        args = parse_cmd_dynamic(cmdline, &bg);
        if(args) {
            print_cmd_args(cmdline, args);
            print_bg(bg);
            int counter=0;
            while(args[counter]!=NULL){
                free(args[counter]);
                counter++;
            }
            free(args);
        }
    }
    return 0;
}
/*******************************************************************/
// This function prints out a message based on the value of bg
// indicating if the command is run in the background or not
void print_bg(int bg) {
    if(bg) {
        printf("run in the background is true\n");
    } else {
        printf("run in the background is false\n");
    }
}

/* This function prints out the cmdline and the argv list.
 *
 * cmdline: the command line string.
 * argv: the argv array of command line argument strings. */
void print_cmd_args(char *cmdline, char **argv ){

    int i=0;

    printf("\nCommand line: %s\n", cmdline);

    while (argv[i] != NULL) {
        /* NOTE: I'm printing out each argv string between '#' characters so that I
         * can see if there is any space or other invisible characters in the
         * argv[i] string (there shouldn't be). */
        printf("%3d  #%s#\n", i, argv[i]);
        i++;
    }
}
