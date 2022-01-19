#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char *argv[])
{
    // a pair of pipes
    // parent process writes and child process reads
    int p_parent[2];
    // child process writes and parent process reads
    int p_child[2];
    // the byte to write or read
    char buf[] = {"Y"};
    pipe(p_parent);
    pipe(p_child);
    if (fork() == 0)
    {
        close(p_parent[1]);
        close(p_child[0]);
        // check whether the length of characters is equal?
        if (read(p_parent[0], buf, 1) != 1)
        {
            printf("fail to read in child process\n");
            exit(1);
        }
        if (write(p_child[1], buf, 1) != 1)
        {
            printf("fail to write in child process\n");
            exit(1);
        }
        printf("%d: received ping\n", getpid());
        exit(0);
    }
    close(p_parent[0]);
    close(p_child[1]);
    if (write(p_parent[1], buf, 1) != 1)
    {
        printf("fail to write in parent process\n");
        exit(1);
    }
    if (read(p_child[0], buf, 1) != 1)
    {
        printf("fail to read in parent process\n");
        exit(1);
    }
    printf("%d: received pong\n", getpid());
    wait(0);
    exit(0);
}
