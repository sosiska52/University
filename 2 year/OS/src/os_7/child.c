#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#define buf 1
int main()
{
srand(time(0));
char symbol;
int value;
int sum = 0;

printf("Consumer\n");
sem_t *full;
sem_t *empty;
sem_t *temp;
const char *sem_full="full";
const char *sem_empty="empty";
const char *sem_temp = "temp";

full= sem_open(sem_full,O_CREAT,0777,0);
empty= sem_open(sem_empty,O_CREAT,0777,buf);
temp = sem_open(sem_temp, O_CREAT, 0777, 0);

while(1){
sem_wait(full);
int num;
sem_getvalue(temp, &num);
value = num - sum;
sum += value;
symbol = (char)value;
printf("Got symbol: ");
for(int i = 0; i < rand()%10;i++)
printf("%c ", symbol);
printf("\n");
sem_post(empty);
}

sem_close(full);
sem_close(empty);
sem_close(temp);
sem_unlink(sem_full);
sem_unlink(sem_empty);
sem_unlink(sem_temp);
return 0;
}

