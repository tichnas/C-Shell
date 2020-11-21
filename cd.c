#include "cd.h"

#include "headers.h"

void cd(char* root, char* cwd, char* newdir) {
  if (newdir == NULL) {
    if (chdir(root) < 0) perror("Error");

  } else if (newdir[0] == '/') {
    if (chdir(newdir) < 0) perror("Error");

  } else {
    char path[1024] = "";

    strcat(path, newdir[0] == '~' ? root : cwd);

    if (newdir[0] != '~') strcat(path, "/");

    strcat(path, newdir + (newdir[0] == '~'));

    if (chdir(path) < 0) perror("Error");
  }
}
