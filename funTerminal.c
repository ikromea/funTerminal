#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "parsecmd.h"

/* The maximum size of your circular history queue. */
#define MAXHIST 10

/*
 * A struct to keep information one command in the history of
 * command executed
 */
struct histlist_t {
    unsigned int cmd_num;
    char cmdline[MAXLINE]; // command line for this process
};

/* Global variables declared here.
 * For this assignment, only use globals to manage history list state.
 * all other variables should be allocated on the stack or heap.
 *
 * Recall "static" means these variables are only in scope in this .c file. */
static struct histlist_t history[MAXHIST];
static int queue_next = 0;  // the next place to insert in the queue

void add_queue(char* cmdline);
void print_queue(void);
char* get_history(int id);
void child_handler(int sig);
char* substr(const char *src, int m, int n);
void clearMemroy(char ** arr);


int main(int argc, char **argv) {
    char cmdline[MAXLINE];
    char **args;
    int bg;
    pid_t pid;

    
    signal(SIGCHLD, child_handler);
    while(1) {
        // (1) print the shell prompt
        printf("Let's party> ");
        fflush(stdout);

        // (2) read in the next command entered by the user
        if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin)) {
            perror("fgets error");
        }
        if (feof(stdin)) { /* End of file (ctrl-D) */
            fflush(stdout);
            exit(0);
        }

     //   printf("DEBUG: %s\n", cmdline);
        args =parse_cmd_dynamic(cmdline, &bg);
       
        if(!strcmp(args[0], "exit")){
            printf("Thanks for partying with us :)\n");
            clearMemroy(args);
            break;
        }
        
        if(args[0][0]== '!'){
            int len = strlen(args[0]);
            char* idString = malloc(sizeof(char)*(len));
            char* substring = substr(args[0], 1,len);
            strcpy(idString,substring);
            free(substring);
            int id = atoi(idString);
            free(idString);
            //printf("%d\n",id);
            if(id==0){
                printf("Invalid input %s\n",args[0]);
                add_queue(cmdline);
            }
            else{
                char* name =get_history(id);
                if(name==NULL){
                    printf("Command %s not found in history\n",idString);
                }
                else{
                    strcpy(cmdline,name);
                    clearMemroy(args);
                    args =parse_cmd_dynamic(cmdline, &bg);
                }
            }
            
        }

        if(!strcmp(args[0], "history")){
            add_queue(cmdline);
            print_queue();
        }

        if(!bg && strcmp(args[0],"history") && !(args[0][0]=='!')){
            int status;
            pid = fork(); // create new process
            if (pid == 0) { /* child */
            if (execvp(args[0],args)<0) {
                printf("%s:Command not found.\n",args[0]);
                exit(0);
            }
            } else { /* parent */
            // wait for child to exit:
                waitpid(pid,&status,0); 
            }
                char *array[3];
                array[0] = "java";
                array[1] = "ShowPicture";
                array[2] = NULL;
                pid = fork(); // create new process
               if (pid == 0) { /* child */
               if (execvp(array[0],array)<0) {
                printf("%s:Command not found.\n","Confetti");
                exit(0);
            }
               }
            
            add_queue(cmdline);
        }
        if(bg  && strcmp(args[0],"history")&& !(args[0][0]=='!')){
            add_queue(cmdline);
            pid = fork(); // create new process
            if (pid == 0) { /* child */
            if (execvp(args[0],args)<0) {
                printf("%s:Command not found.\n",args[0]);
                exit(0);
            }
            }
        }
        clearMemroy(args);
    }
    return 0;
}
// add the val to the circular queue
// update its state to reflect that
// a new value has been added 
void add_queue(char* cmdl) {

  strcpy(history[queue_next%MAXHIST].cmdline,cmdl);
  history[queue_next%MAXHIST].cmd_num=queue_next+1;
  queue_next++;
 



}
/*****************************************/
// print out the values in order that they
// were added to the queue: first to last
// print:  bucket_index_value: bucket_value
//
void print_queue(void){
  int ind = queue_next % MAXHIST;


  while(ind < MAXHIST && queue_next > MAXHIST){
      printf("%d:%s\n", history[ind].cmd_num,history[ind].cmdline);
      ind += 1;
  }


  ind = 0;
  while(ind < (queue_next % MAXHIST)){
      printf("%u:%s\n",history[ind].cmd_num,history[ind].cmdline);
      ind += 1;
  }
}
//problem is here
char* get_history(int id){
    int low = queue_next;
    if (MAXHIST < low){
        low = MAXHIST;
    }

    for (int i = 0; i < low; i++){
        if (history[i].cmd_num == id){
            printf("%s \n", history[i].cmdline);
            return history[i].cmdline;
        }
    }

    return NULL;
}

void child_handler(int sig) {
    int child_status;
    pid_t pid;
    while((pid = waitpid(-1, &child_status, WNOHANG)) > 0){
        //ccount--;
        //printf("signal %d from %d\n",sig, pid);
    }
}

char* substr(const char *src, int m, int n)
{
    // get the length of the destination string
    int len = n - m;
 
    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
 
    // extracts characters between m'th and n'th index from source string
    // and copy them into the destination string
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }
 
    // null-terminate the destination string
    *dest = '\0';
 
    // return the destination string
    return dest - len;
}

void clearMemroy(char ** arr){
    int i = 0;
    while(arr[i] != NULL){
        free(arr[i]);
        i += 1;
    }
    free(arr);
}