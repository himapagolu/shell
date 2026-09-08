#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  //to keep REPL running
  //REPL stands for Read-Eval-Print Loop.
  while(1){
   
  //standard $ sign 
  printf("$ ");

  //input from user
  char command[1024];
  fgets(command,sizeof(command),stdin);

  //to remove extra new line added when user presses enter
  //strcspn = stringcompliment span - basically returns the span of the unmatched/rejected characters that doesn't match. returns the index of the first occurrence of any character in the second string in the first string. 
  command[strcspn(command,"\n")] = '\0';

  //strncmp - string n elem comaparision = compares the first n characters of two strings. 
  if(strncmp(command , "echo " , 5) == 0){
    printf("%s\n",command + 5);
  }
  //to exit out of shell
  //strcmp - string compare = compares two strings and returns 0 if they are equal.
  else if(strcmp(command,"exit") == 0){
    break;
  }
  else if(strncmp(command,"type ",5) == 0){
    if(strcmp(command + 5, "exit") == 0|| strcmp(command + 5, "echo") == 0 || strcmp(command + 5, "type") == 0){
      printf("%s is a shell builtin\n" , command+5);
    }else {
      printf("%s: not found\n", command+5);
    }
    
  }else{
    printf("%s: command not found\n",command);
  }

  }

  return 0;
}


