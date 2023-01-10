/*
1. Taking input
2. tokenizing string / parsing
3. Executing the commands taken as input
*/

#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>



char* command;
//char* argument_list[];
char* input()
{
    command = malloc(sizeof(char) * 1000);
    int ch;
    int n=0;
    while (1) {
    // Read a character
    ch = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (ch == EOF || ch == '\n') {
      command[n] = '\0';
      return command;
    } else {
      command[n] = ch;
    }
    n++;

}
return command;
}

char* parse()
{
   
}

int main()
{
   printf("%s", input()) ;
}
