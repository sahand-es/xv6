#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main() {
  int pid_a = fork();
  int pid_b = fork();
  int pid_c = fork();

  if (pid_a && pid_b && pid_c) {
    char *args[] = { "pstree", 0 };
    exec("pstree", args);
  } else {
    sleep(1);
  }
}
