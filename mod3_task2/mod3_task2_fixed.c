#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{

	printf("My pid is %d\n", getpid());

	sleep(1);

  if ( strcmp(argv[0],"2") != 0) 
  	      execl("mod3_task2_fixed","2",argv[1],NULL);

  if (strcmp(argv[0],"2") == 0)  //Выводит строку,которая была передана при перов запуске программы
	        printf("%s\n",argv[1]);        

	return 0;
}