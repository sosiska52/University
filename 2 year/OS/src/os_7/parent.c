#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <unistd.h>
#define buf 1
int main()
{
char symbol;
int value;

printf("Producer\n");
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
sem_wait(empty);
printf("Enter symbol: ");
scanf(" %s", &symbol);
value = (int)symbol;

for(int i = 0; i < value; i++){
	sem_post(temp);
}
sem_post(full);
}

sem_close(full);
sem_close(mutex);
sem_unlink(sem_full);
sem_unlink(sem_empty);
return 0;
}
