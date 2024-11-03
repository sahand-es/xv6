#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    struct sysinfo_data data;

    if (sysinfo(&data) < 0) {
        printf("sysinfo call failed\n");
        exit(1);
    }

    printf("Free Memory: %d bytes\n", data.free_memory);
    printf("Running Processes: %d\n", data.running_processes);

    exit(0);
}
