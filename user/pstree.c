#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"

void _pstree_print(struct process_data node, struct process_data list[], int length, int depth) {
  for (int i = 0; i < depth; i++) {
    printf("——");
  }

  printf("[%d] %s (status: ", node.pid, node.name);
  switch (node.state) {
  case P_RUNNING:
    printf("Running");
    break;
  case P_RUNNABLE:
    printf("Runnable");
    break;
  case P_SLEEPING:
    printf("Sleeping");
    break;
  case P_ZOMBIE:
    printf("Zombie");
    break;
  }
  printf(")\n");

  for (int i = 0; i < length; i++) {
    if (list[i].parent_pid == node.pid) {
      _pstree_print(list[i], list, length, depth + 1);
    }
  }
}

int main(int argc, char *argv[]) {
  struct process_data list[NPROC];
  struct process_data init;

  int length = 0;
  int pid = 0;
  while (1) {
    struct process_data data;
    int result = next_process(pid, &data);
    if (!result) {
      break;
    }
    list[length] = data;
    if (data.pid == 1) {
      init = data;
    }
    pid = data.pid;
    length++;
  }

  _pstree_print(init, list, length, 0);

  return 0;
}
