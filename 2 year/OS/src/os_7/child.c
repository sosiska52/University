#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {

key_t shm_key;
    int shm_id;
    char *shm_ptr;
    const char *shm_name = "/shared_memory";

    // Генерируем уникальный ключ для сегмента разделяемой памяти
    shm_key = ftok(".", 'R');
    if (shm_key == -1) {
        perror("ftok");
        exit(1);
    }

    // Получаем сегмент разделяемой памяти, созданный отправителем
    shm_id = shmget(shm_key, sizeof(char), 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    // Присоединяем сегмент разделяемой памяти
    shm_ptr = (char *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (void*) -1) {
        perror("shmat");
        exit(1);
    }

    sem_t *sem1 = sem_open("/semaphore1", O_CREAT, 0644, 1); // Создание семафора
    sem_t *sem2 = sem_open("/semaphore2", O_CREAT, 0644, 0); // Создание семафора

    if (sem1 == SEM_FAILED || sem2 == SEM_FAILED) {
        perror("Ошибка создания семафора");
        return 1;
    }


    while (1) {
        sem_wait(sem2); // Ожидание семафора
	char symbol = *shm_ptr;
        printf("Процесс 2 получил символ: %c. \n", symbol);

        int numPrints = rand() % 10 + 1; // Генерация случайного количества повторений

        for (int i = 0; i < numPrints; i++) {
            printf("Символ %c выводится на экран (раз %d/%d)\n", symbol, i + 1, numPrints);
            usleep(50000); // Задержка в микросекундах
        }

        sem_post(sem1); // Установка семафора
    }
// Отсоединяем сегмент разделяемой памяти
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }
    sem_close(sem1); // Закрытие семафора
    sem_close(sem2); // Закрытие семафора

    return 0;
}

