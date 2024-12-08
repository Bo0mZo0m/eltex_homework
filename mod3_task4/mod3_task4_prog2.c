#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <string.h>



struct message_text {

    char buf[200];
};

struct message {

    struct message_text ms_text;
};


int main(int argc, char *argv[])
{

    key_t key,mskey,mskey2;
    int semid,msid,msid2;
    int counter;
    int res;
    struct sembuf buf[2];
    struct message my_message,return_message;
    char* turns[] = {"e5","c6","c5","b4", "a5","d4","f6","NULL"};

    if ((key = ftok("mod3_task4_prog1.c", 1)) == -1) {
        perror ("ftok");
        exit (1);
    }

    if ((semid = semget(key, 2, 0) == -1)) {
        perror ("semget");
        exit (1);
    }


    if ((mskey = ftok ("mod3_task4_prog1.c", 1)) == -1) {
        perror ("ftok");
        exit (1);
    }

    if ((msid = msgget (mskey, 0660 | IPC_CREAT)) == -1) {
        perror ("semget");
        exit (1);
    }

    if ((mskey2 = ftok ("mod3_task4_prog2.c", 1)) == -1) {
        perror ("ftok");
        exit (1);
    }

    if ((msid2 = msgget (mskey2, 0666 | IPC_CREAT)) == -1) {
        perror ("msgget");
        exit (1);
    }


    buf[0].sem_num = 0;
    buf[0].sem_flg = SEM_UNDO;
    buf[1].sem_num = 1;
    buf[1].sem_flg = SEM_UNDO;
 
    counter = 0;
    res = 1;

        while (counter < 20) {

            if (res == 0)
            {
                printf("У черных закончились ходы\n");
                exit(0);
            }

            buf[0].sem_op = 0;
            semop(semid, buf, 1);


            strcpy(my_message.ms_text.buf,turns[counter]);
           if (msgsnd (msid2, &my_message, sizeof (struct message_text), 0) == -1) 
            {
              perror ("msgsnd");
              exit (1);
            }

             if (msgrcv (msid, &return_message, sizeof (struct message_text), 0, 0) == -1) 
             {
               perror ("msgrcv");
               exit (1);
             }

            res = strcmp(my_message.ms_text.buf, "NULL");
    
             if (strcmp(return_message.ms_text.buf,"NULL") == 0)
            {
               printf("У белых закончились ходы\n");
                exit(0);
            }
            buf[0].sem_op = 1;
            buf[1].sem_op = -1;
            semop(semid, buf, 2);
            printf("Ход черных:%s\n", my_message.ms_text.buf ); 
            counter++; 
            sleep(3);
        }
    
    return 0;
}