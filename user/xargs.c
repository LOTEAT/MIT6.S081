#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
int main(int argc, char *argv[])
{
	char* args[MAXARG];
	int i = 1, j = 0;
	for(; i < argc; i++)
		args[j++] = argv[i];
	char block[32];
	char buffer[32];
	char* p = buffer;
	// read the output
	int len;
	while((len = read(0, block, sizeof block)) > 0)
	{
		int k = 0, l = 0;
		for(; k < len; k++)
		{
			if(block[k] == '\n')
			{
				buffer[l] = 0;
                l = 0;
                args[j++] = p;
                p = buffer;
                args[j] = 0;
                j = argc - 1;
                if(fork() == 0){
                    exec(argv[1], args);
                }                
                wait(0);	
			}
			else if(block[l] == ' ')
			{
			    buffer[l++] = 0;
                args[j++] = p;
                p = &buffer[l];
            }
            else 
            {
                buffer[l++] = block[k];
            }	
			
		}
	}
	exit(0);
}