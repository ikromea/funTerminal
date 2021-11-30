#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parsecmd.h"

char **parse_cmd_dynamic(const char *cmdline, int *bg) {
    char **result = NULL;
    int atToken = 0;
    int numOfTokens=0;
    int lenOfToken=0;
    int currentToken=0;
    int substrStart = -1;
    *bg =0;
    int len = strlen(cmdline);

    //couting the number of strings and stopping if there is an &
    for(int i =0;i < len;i++){
        if(cmdline[i]== '&'){
            *bg=1;
            break;
        }
        else if(isspace(cmdline[i]) && atToken){
            atToken=0;
        }
        else if(!isspace(cmdline[i]) && !atToken){
            atToken=1;
            numOfTokens++;
        }
    }

    if(substrStart!=-1){
        numOfTokens++;
    }


    result=malloc(sizeof(char*)*(numOfTokens+1));
    atToken = 0;

    for(int i =0;i<len;i++){
     if(cmdline[i]== '&'){
         //If we are at a token, store this token and break
            if(atToken){
                result[currentToken]= malloc(sizeof(char)*(lenOfToken+1));
                for(int j=substrStart;j<i;j++){
                    result[currentToken][j-substrStart]= cmdline[j];
                }
                result[currentToken][i-substrStart]= '\0';
            }
            break;
        }
        else if(isspace(cmdline[i]) && atToken){
            //If we reach a space and we were at a token, we want to store this token
            atToken=0;
            result[currentToken]= malloc(sizeof(char)*(lenOfToken+1));
            for(int j=substrStart;j<i;j++){
                result[currentToken][j-substrStart]= cmdline[j];
            }
            result[currentToken][i-substrStart]= '\0';
            substrStart = -1;
            currentToken++;

        }
        else if(!isspace(cmdline[i]) && !atToken){
            //If we are at a non-space and we are not at a token we start
            //a new token count
            atToken=1;
            lenOfToken=1;
            substrStart=i;
        }
        else if(!isspace(cmdline[i]) && atToken){
            //If we are at a non space and at a token, we incremement lenght
            //by 1
            lenOfToken++;
        }
    }

    if(substrStart!=-1){
        //Add the last thing to the 
        if(!bg){
        result[currentToken]= malloc(sizeof(char)*(lenOfToken+1));
            for(int j=substrStart;j<len;j++){
                result[currentToken][j-substrStart]= cmdline[j];
            }
            result[currentToken][len-substrStart]= '\0';
        }
    }
    //set the last thing to NULL
    result[numOfTokens] = NULL;

    return result;
}

