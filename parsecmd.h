#ifndef _PARSECMD__H_
#define _PARSECMD__H_

#define MAXLINE    1024   // max command line size
#define MAXARGS     128   // max number of arguments on a command line

/*
* parse_cmd_dynamic - Parse the passed command line into an argv array.
*
*    cmdline: The command line string entered at the shell prompt
*             (const means that this function cannot modify cmdline).
*             Your code should NOT attempt to modify these characters!
*
*         bg: A pointer to an integer, whose value your code should set.
*             The value pointed to by bg should be 1 if the command is to be
*             run in the background, otherwise set it to 0.
*
*    returns: A dynamically allocated array of strings, each element
*             stores a string corresponding to a command line argument.
*             (Note: the caller is responsible for freeing the returned
*             argv list, not your parse_cmd_dynamic function).
*/
char **parse_cmd_dynamic(const char *cmdline, int *bg);
//DO NOT CHANGE parse_cmd_dynamic's parameter / return types!


#endif
