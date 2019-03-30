#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <malloc.h>
#include <stdlib.h>

#define PIPE_READ 0
#define PIPE_WRITE 1

void *malloc_check(size_t bytes) {
    void *result = malloc(bytes);

    if (result == NULL) {
        perror("malloc error");
        exit(-1);
    }

    return result;
}

void close_pipe(int **pipe_fds, size_t pipes_count) {
    for (size_t i = 0; i < pipes_count; ++i) {
        close(pipe_fds[i][PIPE_READ]);
        close(pipe_fds[i][PIPE_WRITE]);
    }
}

void m_perror(char *message, int code) {
    perror(message);
    exit(code);
}

int main(int argc, char **argv) {
    size_t programs_count = (size_t)argc - 1;
    size_t pipes_count = programs_count - 1;

    int **pipe_fds = (int **)malloc_check(pipes_count * sizeof(int **));

    for (size_t i = 0; i < pipes_count; ++i) {
        pipe_fds[i] = (int *)malloc_check(2 * sizeof(int));

        if (pipe(pipe_fds[i]) == -1) {
            m_perror("pipe error", -1);
        }
    }

    for (size_t i = 0; i < programs_count; ++i) {
        pid_t pid = fork();

        if (pid  < 0) { //error
            m_perror("fork error", -1);
        }

        if (pid == 0) { //child
            if (i != 0) {
                if (dup2(pipe_fds[i - 1][PIPE_READ], STDIN_FILENO) == -1) {
                    m_perror("dup2 error", -1);
                }
            }

            if (i != programs_count - 1) {
                if (dup2(pipe_fds[i][PIPE_WRITE], STDOUT_FILENO) == -1) {
                    m_perror("dup2 error", -1);
                }
            }

            close_pipe(pipe_fds, pipes_count);

            if (execlp(argv[i + 1], argv[i + 1], NULL) == -1) {
                m_perror(argv[i + 1], -1);
            }
        }
    }

    close_pipe(pipe_fds, pipes_count);

    for (size_t i = 0; i < programs_count; ++i) {
        wait(NULL);
    }

    //free
    for (size_t i = 0; i < pipes_count; ++i) {
        free(pipe_fds[i]);
    }
    free(pipe_fds);

    return 0;
}