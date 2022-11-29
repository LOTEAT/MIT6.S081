#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void filter(int* primes, int n){
    printf("prime %d\n", primes[0]);
    if(n == 1)
        return;
    int p[2];
    pipe(p);
    int count = 0;
    for(; count<n; count++){
        if(primes[count] % primes[0])
            write(p[1], primes + count, 4);
    }
    close(p[1]);
    if(fork()==0){
        int number;
        int offset = 0;
        while (read(p[0], &number, 4) == 4)
        {
            *(primes + offset) = number;
            offset++;
        }
        filter(primes, offset);
        // terminate the child process
        exit(0);
    }
    wait(0);
}
int main(int argc, char *argv[])
{
    int primes[34];
    for(int i=2; i<=35; i++){
        primes[i - 2] = i;
    }
    filter(primes, 34);
    exit(0);
}