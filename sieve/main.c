#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <lzma.h>
#include <zconf.h>

typedef unsigned long long ULL;

int main(int argc, char **argv) {
    ULL search_limit =
            argc < 2 ? ULLONG_MAX : strtoull(argv[2], NULL, 10);
    ULL threads_count = strtoull(argv[1], NULL, 10);

    pid_t pid = 0;

    for (ULL i = 0; i < threads_count; ++i) {
        pid = fork();

        if (pid < 0) {
            perror("fork error");
            exit(-1);
        } else if (pid > 0) { //child

        }
    }

    printf("search limit: %llu", search_limit);
    return 0;
}