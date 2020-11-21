#include "command.h"

#include "headers.h"

void getCommands(char* command, char** commands) {
  char* str = NULL;
  long unsigned size = 1024;

  int len = getline(&str, &size, stdin);

  strcpy(command, str);

  str[len - 1] = '\0';

  commands[0] = NULL;

  if (str[0] == '\0') return;

  char* token = strtok(str, ";");

  for (ll i = 0; token != NULL; i++) {
    commands[i] = token;
    commands[i + 1] = NULL;
    token = strtok(NULL, ";");
  }
}
