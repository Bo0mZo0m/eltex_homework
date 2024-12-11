#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

void new_hdl(int sig)
{
   printf("Обработчик сигнала для потока %ld получил сигнал %d\n", pthread_self(),sig );
   sleep(2);
   printf("Обработка завершена\n");
}

void* pthread1(void* arg)
{
	sigset_t set;
	sigemptyset(&set);
	sigfillset(&set);
	pthread_sigmask(SIG_BLOCK,&set,NULL);
	printf("Поток: %s = %ld блокируеют любой сигнал, кроме SIGKILL и SIGSTOP.\n", (char*)arg,pthread_self());
	sleep(5);
	printf("Поток: %s успешно завершил свою работу.\n", (char*)arg);
	pthread_exit(0);


}
void* pthread2(void* arg)
{
	printf("Поток: %s = %ld обработает сигнал SIGINT обработчиком\n", (char*)arg,pthread_self());
	sleep(4);
	pthread_exit(0);

}
void* pthread3(void* arg)
{
	printf("Поток: %s = %ld ждёт сигнал SIGQUIT\n", (char*)arg,pthread_self());
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGQUIT);
	int sig;
	sigwait(&set,&sig);


}

int main()
{
	struct sigaction siga;
	memset(&siga,0,sizeof(siga));
	siga.sa_handler = new_hdl;
	sigaction(SIGINT,&siga,0);

	char p_th1[] = "pth1";
	char p_th2[] = "pth2";
	char p_th3[] = "pth3";

	pthread_t pth1,pth2,pth3;

	pthread_create(&pth1,NULL, pthread1, (void*)p_th1);
	pthread_create(&pth2,NULL, pthread2, (void*)p_th2);
	pthread_create(&pth3,NULL, pthread3, (void*)p_th3);

	sleep(1);

	pthread_kill(pth1,SIGTERM);

	sleep(2);

	pthread_kill(pth2,SIGINT);

	sleep(4);

	pthread_kill(pth3,SIGQUIT);

	


	return 0;
}