#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 10
#define FIFO_SIG "fifo_sig"

void abrt_handler(int i) {
	
   char text[] = "SIGABRT signal was received";
   char buf[BUFSIZE];
 
   unlink(FIFO_SIG);
   if (mkfifo(FIFO_SIG, 0777))
      {
        fprintf(stderr, "mkfifo");
        exit(EXIT_FAILURE);
      } 

   int fd_fifo; 
   if (fd_fifo = open(FIFO_SIG, O_RDWR) == -1) // выводит 0
      {
        fprintf(stderr, "Error open");
        exit(EXIT_FAILURE);
      }

   write(fd_fifo, text, strlen(text));
   if(read(fd_fifo, &buf, sizeof(buf)) == -1)
      {
        fprintf(stderr, "Error read");
        exit(EXIT_FAILURE);
      } else {
        printf("\n%s \n", buf);
      }
   exit(EXIT_SUCCESS);
   unlink(FIFO_SIG);
}

int main(int argc, char ** argv) {
struct sigaction siga;
siga.sa_handler = abrt_handler;
printf("My pid is %i\n", getpid());
printf("Waiting...\n");
sigaction(SIGABRT,&siga,0);
while(1) sleep(1);
return EXIT_FAILURE;
}