#include "prompt.h"

#include "headers.h"

void printPrompt(int* bgPid, char** bgCommand, char* user, char* root,
                 char* cwd, char* hostname) {
  char path[1024] = " ";

  for (ll i = 0;; i++) {
    if (root[i] == '\0') {
      path[0] = '~';
      break;
    } else if (cwd[i] == '\0' || cwd[i] != root[i]) {
      break;
    }
  }

  if (path[0] == '~') {
    strcat(path, cwd + strlen(root));
  } else {
    strcpy(path, cwd);
  }

  int status;
  for (int i = 0; i < 100; i++) {
    if (bgPid[i]) {
      if (waitpid(bgPid[i], &status, WNOHANG) > 0) {
        fprintf(stderr, "%s with PID %d exited %s\n", bgCommand[i], bgPid[i],
                WIFEXITED(status) ? "normally" : "abnormally");

        bgPid[i] = 0;
        free(bgCommand[i]);
      }
    }
  }

  printf("<\033[01;32m%s@%s\033[01;00m:\033[01;34m%s\033[01;00m>", user,
         hostname, path);
}
