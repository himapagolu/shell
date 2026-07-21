#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  //to keep REPL running
  while(1){
   
  //standard $ sign 
  printf("$ ");

  //input from user
  char command[1024];
  fgets(command,sizeof(command),stdin);

  //to remove extra new line added when user presses enter
  command[strcspn(command,"\n")] = '\0';

  if(strncmp(command , "echo " , 5) == 0){
    printf("%s\n",command + 5);
  }
  //to exit out of shell
  else if(strcmp(command,"exit") == 0){
    break;
  }
  else if(strncmp(command,"type ",5) == 0){
    if(strcmp(command + 5, "exit") == 0|| strcmp(command + 5, "echo") == 0 || strcmp(command + 5, "type") == 0){
      printf("%s is a shell builtin\n" , command+5);
    }else{
      printf("%s: not found\n", command+5);
    }
    
  }else{
    printf("%s: command not found\n",command);
  }

  }

  return 0;
}