#include "runner.h"

#include "headers.h"

void runCommand(int* bgPid, char** bgCommand, int background, char** args) {
  int pid = fork();

  if (pid < 0) {
    perror("Error");

  } else if (pid) {
    if (background) {
      printf("%s started with PID %d\n", args[0], pid);

      for (int i = 0; i < 100; i++) {
        if (!bgPid[i]) {
          bgPid[i] = pid;
          bgCommand[i] = malloc(strlen(args[0]) + 1);
          strcpy(bgCommand[i], args[0]);
          break;
        }
      }

    } else {
      waitpid(pid, NULL, 0);
    }

  } else {
    if (background) setpgid(0, 0);

    if (execvp(args[0], args) < 0) {
      perror("Error");
      exit(1);
    }
  }
}
