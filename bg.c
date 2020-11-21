#include "bg.h"

#include "headers.h"

int tichnas_bg(int pid) {
  if (kill(pid, SIGCONT) < 0) {
    perror("Error");
    return -1;
  }

  return 0;
}