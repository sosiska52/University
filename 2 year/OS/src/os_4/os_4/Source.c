#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
	pid_t pid;
	printf("������� 0 PID = %d PPID = %d\n", getpid(), getppid());

	// ���������� ������� ��������
	if ((pid = fork()) == -1)
		printf("������!\n");
	else if (pid == 0) {
		printf("���������� �������� 1 PID = %d PPID = %d\n", getpid(),
			getppid());

		// ���������� ������� ��������
		if ((pid = fork()) == -1)
			printf("������!\n");
		else if (pid == 0) {
			printf("���������� �������� 2 PID = %d PPID = %d\n", getpid(),getppid());

			// ���������� ���������� ��������
			if ((pid = fork()) == -1)
				printf("������!\n");
			else if (pid == 0) {
				printf("���������� �������� 4 PID = %d PPID = %d\n",getpid(), getppid());
				printf("���������� ������� 4 PID = %d PPID = %d\n",getpid(), getppid());
				exit(0);
			}
			printf("���������� ������� 2 PID = %d PPID = %d\n", getpid(),getppid());
			exit(0);
		}
		else sleep(1);//�������� ������������� �������� (2 ������� sleep)

		// ���������� �������� ��������
			if ((pid = fork()) == -1)
				printf("������!\n");
			else if (pid == 0) {
				printf("���������� 3 PID = %d PPID = %d\n", getpid(), getppid());

				//���������� ������ �����
				if ((pid = fork()) == -1)
					printf("������!\n");
				else if (pid == 0) {
					printf("���������� 5 PID = %d PPID = %d\n", getpid(), getppid());
					printf("���������� ������� 5: PID = %d, PPID = %d\n",getpid(), getppid());
					exit(0);
				}
				else sleep(1);

				//���������� ������� �����
				if ((pid = fork()) == -1)
					printf("������!\n");
				else if (pid == 0) {
					printf("���������� 6 PID = %d PPID = %d\n", getpid(), getppid());

					//���������� �������� �����
					if ((pid = fork()) == -1)
						printf("������!\n");
					else if (pid == 0) {
						printf("���������� 7 PID = %d PPID = %d\n", getpid(), getppid());
						printf("���������� ������� 7: PID = %d, PPID = %d\n", getpid(), getppid());
						exit(0);
					}
					else sleep(1);
					printf("���������� ������� 6: PID = %d, PPID = %d\n", getpid(), getppid());
					exit(0);
				}
				else sleep(1);

				printf("���������� ������� 3: PID = %d, PPID = %d\n",
					getpid(), getppid());
				execl("/bin/pwd", "pwd", NULL);
			}
			else sleep(1);//�������� ������������� �������� (1 ������� sleep)
		printf("���������� ������� 1: PID = %d, PPID = %d\n", getpid(),
			getppid());
		exit(0);
	}
	else sleep(3);//�������� ������������� �������� (0 ������� sleep)
	printf("���������� ������� 0: PID = %d, PPID = %d\n", getpid(),
		getppid());
	return 0;
}