#include "kernel/types.h"
#include "user/user.h"

int main() {
  const int BLOCK_SIZE = 4096;

  char* memory = sbrk(BLOCK_SIZE);

  if (memory == (char*)-1) {
    printf("failed to allocate\n");
    return 1;
  }

  // fill
  for (int i = 0; i < BLOCK_SIZE; i++)
    memory[i] = (char)(i % 256);

  // check
  for (int i = 0; i < BLOCK_SIZE; i++) {
    if (memory[i] != (char)(i % 256)) {
      printf("verification failed at offset %d\n", i);
      return 1;
    }
  }

  printf("ok\n");
  return 0;
}
