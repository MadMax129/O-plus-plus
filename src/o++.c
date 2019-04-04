#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "o++.h"
#include "errors.h"
//#include <ctype.h>

#define MAX_LENGTH 1000

void lex_class(char toks[100][100]);

typedef enum
{
  IGNORE,
  FIND_CLASS,
  COPY_CONT,
  FIND_ALL,
  COPY_STRING,
  PRINT_TOK,
} States;


// Conditions for Ignoring not working GLOBALLY
// char *str_delim_def = " \t\n";
// char *str_delim = str_delim_def;


// Storing Tokens
char tokens[100][100] = {};
char class_tokens[100][100] = {};
char variables[100][100] = {};
char ignore[100][100] = {};
// Tokens variables
int idx = 0;
int i;


int main(int argc, char *argv[])
{
  States state = FIND_CLASS;
  FILE *file;

  file = fopen(argv[1], "rt");
  if (file == NULL)
  {
    printf("NO FILE NAMED %s\n", argv[1]);
    return -1;
  }

  const char *str_delim_def = " \t\n";
  const char *str_delim = str_delim_def;
  char fline[255];


  while (fgets(fline, MAX_LENGTH, file) != NULL)
  {

    char *sword = strtok(fline, str_delim);

    while (sword != NULL)
    {
      //printf("[%s] state=%d\n", sword, state);

      switch(state)
      {

        case IGNORE:

          if (strcmp(sword, ">") == 0)
          {
            state = FIND_ALL;
          }
          sword = "";
        break;

        case FIND_CLASS:

          if (strcmp(sword, "class") == 0)
          {
            state = COPY_CONT;
          }
          else if (strcmp(sword, "noclass") == 0)
          {
            //printf("NO CLASS continuing...\n");
            state = FIND_ALL;
          }
          else
          {
            printf("CLASS DECLARATION MISSING\n");
            exit(1);
          }
        break;

        case COPY_CONT:
          if (strcmp(sword, "end") == 0)
          {
            // STILL IN PROGRESS
            lex_class(class_tokens);

            state = FIND_ALL;
          }
          strcpy(class_tokens[idx], sword);
          idx++;
        break;

        case FIND_ALL:
          // ## COMMENTS WORKING ##
          if (strcmp(sword, "<") == 0)
          {
            //printf("FOUND COMMENT\n");
            state = IGNORE;
          }
          else if (strcmp(sword, "print") == 0)
          {
            str_delim = "\n";
            state = PRINT_TOK;
          }
          else if (strcmp(sword, "") == 0)
          {
            state = FIND_ALL;
          }
          else
          {
            printf("SYNTAX ERROR %s\n", sword);
            exit(1);
          }
        break;

        case PRINT_TOK:
        if ((sscanf(sword, " (' %[^'\n] ') ", tokens) == 1) || (sscanf(sword, " ' %[^'\n] ' ", tokens) == 1))
        {
          printf("%s \n", tokens);
          str_delim = str_delim_def;
          state = FIND_ALL;
        }
        else
        {
          printf("SYNTAX PRINT ERROR %s \n", sword);
          exit(1);
        }
        break;

      }

      // FINISH SO NOT GOES BACK TO FIND CLASS
      //if (force_next_line == 1) { break; }

      sword = strtok(NULL, str_delim);
    }
  }
}


// TODO FIX SSCANF
void lex_class(char toks[100][100])
{
  Tok t = VAR; // USE LATER TO RETURN TOK
  Variable vv;
  Variable *vptr = &vv;

  if (strcmp(*toks, "") == 0)
  {
    ERROR_FOUND(1);
    exit(1);
  }

  for (i=0;i<idx;i++)
  {
    //printf("--> %s\n", toks[i]);

    switch (t)
    {
      case VAR:
        if (sscanf(toks[i], "@%s", vptr->var_name[var_count]) == 1)
        {
          var_count++;
          // printf("%s\n", vptr->var_name);
          // i is always one less than idx
          // TODO Make quit with error if switchcannot be completed 
          printf("%d | %d\n", i,idx);
          t = EQ;

        }
        else
        {
          ERROR_FOUND(2);
          exit(1);
        }
      break;

      case EQ:
        if (strcmp(toks[i], ":") == 0)
        {
          //printf("EQUALS FOUND\n");
          t = TYPE;
        }
        else {ERROR_FOUND(3); exit(1);}

      break;

      case TYPE:
        // NO TYPE IF FILE THROW ERROR IF NO TYPE FOUND
        //printf("HERE AT TYPE\n");
        if (*toks[i] >= '0' && *toks[i] <= '9')
        {
          int num = atoi(toks[i]);
          vptr->val[var_num_count] = num;
          var_num_count++;
        }
        else
        {
          printf("Var is not equal to a Number: %s\n", toks[i]);
        }

        t = VAR;

      break;

    }


  }

// Check if var names and values are alligned
  for (i=0;i<var_count && var_num_count;i++)
  {
    printf("Name: %s Value: %d\n", vptr->var_name[i], vptr->val[i]);
  }


// Not giving error but not going into the if
  // if (sscanf(*toks, " @ %[^\n] ", vptr->var_name) == 1)
  // {
  //   printf("WERE EHRE\n");
  //   printf("%s \n", vptr->var_name);
  // }
  // if (strcmp(*toks, "@") == 0)
  // {
  //   printf("VARIABLE\n");
  // }
  // else if (strcmp("", *toks) == 0)
  // {
  //   ERROR_FOUND(1);
  //   exit(1);
  // }
  // else
  // {
  //   ERROR_FOUND(2);
  //   exit(1);
  // }


}
