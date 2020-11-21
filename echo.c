#include "echo.h"

#include "headers.h"

void echo(char* string) {
  char* token;
  token = strtok(string, " \t");

  while (token != NULL) {
    for (ll i = 0; token[i] != '\0'; i++) printf("%c", token[i]);

    token = strtok(NULL, " \t");
    printf(" ");
  }

  printf("\n");
}