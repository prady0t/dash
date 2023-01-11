/*
1. Taking input
2. tokenizing string / parsing
3. Executing the commands taken as input
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
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

char** parse(char* input)
{
    int position = 0;
    char** arguments = malloc(sizeof(char*)*1000);
    char* inputed;
    inputed = strtok(input," ");
    while(inputed != NULL)
    {
        arguments[position] = inputed;
        printf("%s",inputed);
        position++;
        
        inputed = strtok(NULL , " ");

    }
    arguments[position] = NULL;
    return arguments;
   
}
// int main()
// {
//      parse("ls -l");
// }

int main() {
    while(1)
    {
        
    printf("\033[1;33m");
     command = input();
    char* argument_list[1000] = {NULL};
    *argument_list = parse(command);
     

    if (fork() == 0) {
         
        
        int status_code = execvp(command, argument_list);

        printf("This won't execute unless it terminates abnormally!\n");

        if (status_code == -1) {
            printf("Terminated Incorrectly\n");
            return 1;
        }
    }
    else {
        // Old Parent process. The C program will come here
        //printf("This line will be printed\n");
        //exit(0);
        
    }
    }

    return 0;
 }
