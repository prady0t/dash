/*
Basic working of Dash shell: 
1. Taking input
2. tokenizing string / parsing
3. checking for built-in functions
4. Executing the commands taken as input
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char* command;
char** argument_list;
char* builtin_functions_name_list[] = {"help","-","cd","about"};

void exit_shell()
{
    printf("Bye Bye");
    exit(0);
}
void about()
{
    system("cat banner.txt");
    printf("\n");
    printf("Simple command line terminal emulator.");
    
}

void cd(char** cmd) 
{
    if(cmd[1] == NULL)
    {
        printf("Wrong Usage! Use cd /directory");
        return ;

    }
    else
    {
       if(chdir(cmd[1]) != 0)
       {
        printf("Directory not found!");
        return ;
       }
       
    }

}

void help()
{
    printf("Uasge (a few built-in commands:\n\n");
    printf(" help -> for list of built-in commands\n");
    printf(" - (a dash) -> exit\n");
    printf(" about -> about the program\n");
}

void init()// set up termianl add colour as green,red.
{
    
    printf("\033[1;32m");
    printf("\n");
    system("cat banner.txt");
    printf("\n");
    system(" echo HELLO $USER");
}
int check_builtins() //returns 0 for false 1 for true
{
    int builtin_number = -1;
    int size = sizeof(builtin_functions_name_list)/sizeof(char *);
    for(int i = 0; i<size; i++)
    {
        if(strcmp(command,builtin_functions_name_list[i]) == 0)
        {
        builtin_number = i;
        break;
        }
    }
    switch (builtin_number)
    {
        

    case 0:
        help();
        return 1;
        

    case 1:
        exit_shell();
        return 1;
        

    case 2:
        cd(argument_list);
        return 1;
        

    case 3:
        about();
        return 1;
        

    default:
    return 0;
        
    }
}



char* input()
{
    command = malloc(sizeof(char) * 1000);
    int ch;
    int n=0;
    while (1) {
    // Read a character
    ch = getchar();
    

    // If we hit EOF, replace it with a null character and return.
    //getchar() returns EOF when at end. 
    if (ch == EOF || ch == '\n') {
      command[n] = '\0';
      return command;
    } 
    
    else {
      command[n] = ch;
    }
    n++;

}
return command;
}

#define DELIMITER " \t\r\n\a"

char** parse(char* input)
{
    int position = 0;
     char** arguments = malloc(sizeof(char*)*1000);
    char* inputed;
    
    inputed = strtok(input,DELIMITER);
    while(inputed != NULL)
    {
        arguments[position] = inputed;
        //printf("%s",arguments[position]);
        position++;
        
        inputed = strtok(NULL , DELIMITER);

    }
    arguments[position] = NULL;
    return arguments;
   
}

int execute()
{
    while(1)
    {
        printf("\n");
        printf("🐚 -> ");
        
    //printf("\033[1;32;40m");//Green \033[1;32m
     command = input();
     printf("\n");
     int status;
     argument_list = parse(command);
     if(check_builtins())
     {
        printf("\n");
     continue;
     }
        
    int pid = fork();

    if (pid == 0) {
         
        //printf("\n");
        int status_code = execvp(command, argument_list);

        printf("\033[5;31m ERROR! Command not found.\n"); //Adding error blinker here

        if (status_code == -1) {
            printf("\033[25;32m\n");
            return 1;
        }
    }
    else {
        // Old Parent process. The C program will come here
        do {
      int wpid = waitpid(pid, &status, WUNTRACED);
    } 
    while (!WIFEXITED(status) && !WIFSIGNALED(status));
        
        
    }
    }

    return 0;

}
 int main()
 {
    //printf("\n");
    init();
    execute();
        
    
 }

