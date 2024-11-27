#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
  int f = fork();

  printf("My pid is %d\n", getpid());

  sleep(1);
  
  printf("Hello World\n");
  
  if (f == 0)
          exit(EXIT_SUCCESS);   

  if (f == 0) 
          execl("mod3_task2","2","Hello World",NULL);
 
  return 0;
}