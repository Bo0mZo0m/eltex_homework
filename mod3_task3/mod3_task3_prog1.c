#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#define N 10

int main()
{
    

    int *array_time;    /* Указатель на разделяемую память */
    int shmid;     /* IPC дескриптор для области разделяемой памяти */
    int new = 1;   /* Флаг необходимости инициализации элементов массива */
    char pathname[] = "mod3_task3_prog2.c";
        
    key_t key;   
 
    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }
   
    if((shmid = shmget(key, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0){
   
        if(errno != EEXIST){
          
            printf("Can\'t create shared memory\n");
            exit(-1);
        } else {
           
            if((shmid = shmget(key, 3*sizeof(int), 0)) < 0){
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
            new = 0;
        }
    }
    

    if((array_time = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
        printf("Can't attach shared memory\n");
        exit(-1);
    }
   

    if (array_time[0] <= 0 && new == 0)
    {
        printf("Техническое поражение белых,черные победили!\n");
        shmdt(array_time);
        exit(0);
    }

    if (array_time[1] <= 0 && new == 0)
    {
        printf("Техническое поражение черных,белые победили!\n");
        shmdt(array_time);
        exit(0);
    }

    if (array_time[6] == 1)
    {
        printf("Нелья ходить дважды\n");
        exit(-1);
    }

    time_t time_start;
    time_t time_end;
    time_t time_result;
    

    if(new){
        time_start = time(NULL);
        array_time[0] = N; // Общее время хода для первой прогрммы (белых)
        array_time[1] = N; // Общее время хода для второй прогрммы (черных)
        array_time[2] = (int)time_start; //Время "старта" первой программы
        array_time[6] = 1; // Флаг для переключения между программами!
        printf("Время пошло!У каждого игрока времени ровно: %d секунд\n",N);
         

    }
    else{
        time_end = time(NULL);
        time_result = time_end - array_time[3]; 
        time_start = time(NULL);
        array_time[0] -=(int)time_result; // Общее время хода для первой прогрммы
        array_time[2] = (int)time_start; //Время "старта" первой программы
        array_time[4] = (int)time_result;//Время "хода" первой программы 
        array_time[6] = 1; // Флаг для переключения между программами!
        printf("Общее время белых %d\n Время хода белых %d\n", array_time[0], array_time[4]);
    }  
    if (array_time[0] <= 0)
    {
        printf("Техническое поражение белых,черные победили!\n");
        shmdt(array_time);
        exit(0);
    }
    
    if(shmdt(array_time) < 0){ 
        printf("Can't detach shared memory\n");
        exit(-1);
    }
   

    return 0;
}









