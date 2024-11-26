#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main() {
  nice(10);
  int pid_a = fork();
  if (pid_a == 0) {
    nice(-1);
    char *args[] = { "pstree", 0 };
    exec("pstree", args);
  } else {
    wait(0);
  }
}
