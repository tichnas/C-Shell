#include "cd.h"
#include "command.h"
#include "echo.h"
#include "headers.h"
#include "history.h"
#include "ls.h"
#include "pinfo.h"
#include "prompt.h"
#include "pwd.h"
#include "runner.h"

char hostname[1024];
char* user;
char* root;

void shellLoop() {
  char* commands[20];
  char cwd[1024];
  int bgPid[100];
  char* bgCommand[100];
  char* token;
  char* args[512];
  int noOfArgs;
  int background;
  char command[1024];

  while (1) {
    getcwd(cwd, 1024);

    printPrompt(bgPid, bgCommand, user, root, cwd, hostname);

    getCommands(command, commands);

    addHistory(root, command);

    for (ll i = 0; commands[i] != NULL; i++) {
      while (commands[i][0] == ' ' || commands[i][0] == '\t') commands[i]++;

      if (commands[i][0] == '\0') continue;

      strcpy(command, commands[i]);

      noOfArgs = 0;
      background = 0;
      args[0] = NULL;

      token = strtok(commands[i], " \t");

      while (token) {
        if (token[0] == '&' && token[1] == '\0') {
          background = 1;
        } else if (token[0] != '\0') {
          args[noOfArgs++] = token;
          args[noOfArgs] = NULL;
        }

        token = strtok(NULL, " \t");
      }

      if (!noOfArgs) {
        printf("Error: No command\n");
        continue;
      }

      if (!strcmp(args[0], "echo")) {
        echo(command + strlen(args[0]) + 1);

      } else if (!strcmp(args[0], "pwd")) {
        pwd(cwd);

      } else if (!strcmp(args[0], "cd")) {
        if (noOfArgs > 2) {
          printf("Error: Too many arguments\n");
          continue;
        }

        cd(root, cwd, args[1]);

      } else if (!strcmp(args[0], "ls")) {
        ls(root, args + 1);

      } else if (!strcmp(args[0], "pinfo")) {
        pinfo(root, args[1]);

      } else if (!strcmp(args[0], "history")) {
        if (noOfArgs > 2) {
          printf("Error: Too many arguments\n");
          continue;
        }

        history(root, args[1]);

      } else {
        runCommand(bgPid, bgCommand, background, args);
      }

      for (int i = 0; i < 512; i++) args[i] = NULL;
    }
  }
}

int main() {
  root = getenv("PWD");
  user = getenv("USER");
  gethostname(hostname, 1024);

  printf(
      "\n\t\033[01;91m  Started Custom C-Shell\n\tSanchit Arora | "
      "2019101047\033[01;00m\n\n");

  shellLoop();

  return 0;
}
