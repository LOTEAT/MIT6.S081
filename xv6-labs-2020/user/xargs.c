#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
int 
main(int argc, char *argv[])
{
	char* args[MAXARG];
  int args_length = 0;
	for(int i=1; i < argc; i++)
		args[args_length++] = argv[i];
	char block[32];
	char buffer[32];
  char* p = buffer;
  int offset = 0;

	int len;
	while((len = read(0, block, sizeof(block))) > 0)
	{
    for(int i=0; i<len; i++){
      // '\n' appears
      if(block[i] == '\n'){
        buffer[offset] = 0;
        offset = 0;
        args[args_length++] = p;
        p = buffer;
        args[args_length] = 0;
        args_length = argc - 1;
        if(fork() == 0){
          exec(argv[1], args);
          exit(0);
        }
        wait(0);
      }
      else if(block[i] == ' '){
        buffer[offset++] = 0;
        args[args_length] = p;
        p = buffer + offset;
      }
      else{
        buffer[offset++] = block[i];
      }
    }
	}
	exit(0);
}