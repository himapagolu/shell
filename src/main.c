#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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
      char *path_env = getenv("PATH");
      char found_path[1024];
      int found = 0;

      if(path_env != NULL){
        // Copy since strtok mutates its input, to safe guard the direct path mutation we have work on the copy 
        char path_copy[4096];
        strncpy(path_copy, path_env, sizeof(path_copy) - 1);
        // added null terminator to safe guard the buffer 
        path_copy[sizeof(path_copy) - 1] = '\0';

        char *dir = strtok(path_copy, ":");
        while(dir != NULL){
          // adds the dir tokens from strtok of path_copy and add it to the found_path buffer with the input we are searching for 
          snprintf(found_path, sizeof(found_path), "%s/%s", dir, command + 5);

          if(access(found_path, X_OK) == 0){
            found = 1;
            break;
          }

          dir = strtok(NULL, ":");
        }
      }

      if(found){
        printf("%s is %s\n", command + 5, found_path);
      } else {
        printf("%s: not found\n", command + 5);
      }
    }
  }

  else{
    // split command into argv tokens by spaces, to pass to execvp
    char *exec_argv[64];
    int exec_argc = 0;

    char *token = strtok(command, " ");
    while(token != NULL && exec_argc < 63){
      exec_argv[exec_argc++] = token;
      token = strtok(NULL, " ");
    }
    // execvp requires NULL-terminated array
    exec_argv[exec_argc] = NULL;

    // empty input, nothing to run
    if(exec_argc == 0){
      continue;
    }


    pid_t pid = fork();

    if(pid == 0){
      // child process — replace itself with the external program
      execvp(exec_argv[0], exec_argv);
      // execvp only returns on failure
      printf("%s: command not found\n",exec_argv[0]);
      exit(1);
    }else if(pid > 0){
      // parent process — wait for child to finish
      int status;
      waitpid(pid, &status, 0);
    }else{
      perror("fork failed");
    }
  }

  }

  return 0;
}





