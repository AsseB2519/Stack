#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include "stack.h"
#include "eval.h"
#include "parser.h"

char* get_delimited(char* line, char** rest)
{
    char* newline;

    if ((newline = (char*)malloc(strlen(line) * sizeof(char))) == NULL) return NULL;
    if ((*rest = (char*)malloc(strlen(line) * sizeof(char))) == NULL) return NULL;

    if (*line == '[') {
        memcpy(newline, line + 2, strlen(line) - 4);
        *(newline + strlen(line) - 4) = '\0';
    }
    if (*line == '\"') {
        memcpy(newline, line + 1, strlen(line) - 2);
        *(newline + strlen(line) - 2) = '\0';
    }

    return newline;
}

STACK* eval(char* line, STACK* init_st)
{


    DATA elem, elem1;
    char* sobra_l, * sobra_d;
    elem.type = LONG;
    char *rest=NULL, *token=NULL;
    STACK* st;
    int* AZ =  CreateAZ();

    //   if (init_st == NULL) init_st = create_stack();
    st = create_stack();

    if (*line == '\"') elem1.type = STRING;
    if (*line == '[') elem1.type = ARRAY;
    line = get_delimited(line, &rest);
    if (elem1.type == STRING) {
        elem1.STRING = line;
        push(init_st, elem1);
        return init_st;
    }

    while ((token = get_token(line, &rest)) != NULL) {
        elem.LONG = strtol(token, &sobra_l, 10);
        elem.DOUBLE = strtod(token, &sobra_d);
        if (strlen(sobra_l) == 0) {
            elem.type = LONG;
            push(st, elem);
        }
        else {
            if (strlen(sobra_d) == 0) {
                elem.type = DOUBLE;
                push(st, elem);
            }
            else {
                if ((*token == '[') || (*token == '\"')) st = eval(token, st);
                else Oprations(st, token, AZ);
            }
        }
        free(line);
        line = rest;
    }

    if (elem1.type == ARRAY) {
        elem1.ARRAY = st;
        push(init_st, elem1);
    }
    // falta meter a stack st como um elemento da stack init_st

    return init_st;
}









/*
char* get_token(char* line, char** rest)
{
    char* token;
    char seps[] = " \t\n\"";
    char* newline = NULL;

    if (line == NULL) return NULL;

    if ((newline = (char*)malloc(strlen(line) * sizeof(char))) == NULL) return NULL;
    strcpy(newline, line);

    token = strtok(newline, seps);
    if (token == NULL) return NULL;

//    if ((*rest = (char*)malloc((strlen(line) - strlen(token)+1)*sizeof(char))) == NULL) return NULL;
    if ((*rest = (char*)malloc((strlen(line)) * sizeof(char))) == NULL) return NULL;

    if (strlen(line) > 1) {
        memcpy(*rest, line + strlen(token) + 1, (strlen(line) - strlen(token) - 1));
        (*rest)[(strlen(line) - strlen(token) - 1)] = '\0';
    }
    else (*rest) = NULL;
 //       strcpy(*rest, line);
 //       (*rest)[strlen(line)] = '\0';
//   if(newline!=NULL) free(newline);

    return token;
}
*/



/*
while ((token = get_token(line, &rest)) != NULL) {
    elem.LONG = strtol(token, &sobra_l, 10);
    elem.DOUBLE = strtod(token, &sobra_d);
    if (strlen(sobra_l) == 0) {
        elem.type = LONG;
        push(init_st, elem);
    }
    else {
        if (strlen(sobra_d) == 0) {
            elem.type = DOUBLE;
            push(init_st, elem);
        }
        else {
            evalOprations(init_st, token, rest);
        }
    }
    if (rest != NULL) {
        strcpy(line, rest);
        free(rest);
    }
    else line = rest;
}
*/
//    print_stack(init_st);
