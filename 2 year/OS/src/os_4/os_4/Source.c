#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
	pid_t pid;
	printf("Процесс 0 PID = %d PPID = %d\n", getpid(), getppid());

	// Порождение первого процесса
	if ((pid = fork()) == -1)
		printf("Ошибка!\n");
	else if (pid == 0) {
		printf("Порождение процесса 1 PID = %d PPID = %d\n", getpid(),
			getppid());

		// Порождение второго процесса
		if ((pid = fork()) == -1)
			printf("Ошибка!\n");
		else if (pid == 0) {
			printf("Порождение процесса 2 PID = %d PPID = %d\n", getpid(),getppid());

			// Порождение четвертого процесса
			if ((pid = fork()) == -1)
				printf("Ошибка!\n");
			else if (pid == 0) {
				printf("Порождение процесса 4 PID = %d PPID = %d\n",getpid(), getppid());
				printf("Завершился процесс 4 PID = %d PPID = %d\n",getpid(), getppid());
				exit(0);
			}
			printf("Завершился процесс 2 PID = %d PPID = %d\n", getpid(),getppid());
			exit(0);
		}
		else sleep(1);//задержка родительского процесса (2 процесс sleep)

		// Порождение третьего процесса
			if ((pid = fork()) == -1)
				printf("Ошибка!\n");
			else if (pid == 0) {
				printf("Порождение 3 PID = %d PPID = %d\n", getpid(), getppid());

				//порождение пятого цикла
				if ((pid = fork()) == -1)
					printf("Ошибка!\n");
				else if (pid == 0) {
					printf("Порождение 5 PID = %d PPID = %d\n", getpid(), getppid());
					printf("Завершился процесс 5: PID = %d, PPID = %d\n",getpid(), getppid());
					exit(0);
				}
				else sleep(1);

				//порождение шестого цикла
				if ((pid = fork()) == -1)
					printf("Ошибка!\n");
				else if (pid == 0) {
					printf("Порождение 6 PID = %d PPID = %d\n", getpid(), getppid());

					//порождение седьмого цикла
					if ((pid = fork()) == -1)
						printf("Ошибка!\n");
					else if (pid == 0) {
						printf("Порождение 7 PID = %d PPID = %d\n", getpid(), getppid());
						printf("Завершился процесс 7: PID = %d, PPID = %d\n", getpid(), getppid());
						exit(0);
					}
					else sleep(1);
					printf("Завершился процесс 6: PID = %d, PPID = %d\n", getpid(), getppid());
					exit(0);
				}
				else sleep(1);

				printf("Завершился процесс 3: PID = %d, PPID = %d\n",
					getpid(), getppid());
				execl("/bin/pwd", "pwd", NULL);
			}
			else sleep(1);//задержка родительского процесса (1 процесс sleep)
		printf("Завершился процесс 1: PID = %d, PPID = %d\n", getpid(),
			getppid());
		exit(0);
	}
	else sleep(3);//задержка родительского процесса (0 процесс sleep)
	printf("Завершился процесс 0: PID = %d, PPID = %d\n", getpid(),
		getppid());
	return 0;
}