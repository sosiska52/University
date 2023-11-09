#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
  pid_t pid;
  //printf("Процесс 0 PID = %d PPID = %d\n", getpid(),getppid());

  // Порождение 1 процесса
  if ((pid = fork()) == -1)
    printf("Ошибка!\n");
  else if (pid == 0) {
    printf("Порождение процесса 1 PID = %d PPID = %d\n", getpid(),
      getppid());

	// Порождение 3 процесса
      if ((pid = fork()) == -1)
        printf("Ошибка!\n");
      else if (pid == 0) {
        printf("Порождение процесса 3 PID = %d PPID = %d\n",getpid(), getppid());
        printf("Завершился процесс 3 PID = %d PPID = %d\n",getpid(), getppid());
        execl("/bin/pwd", "pwd", NULL);
      } //else sleep(0.5);

    // Порождение 2 процесса
    if ((pid = fork()) == -1)
      printf("Ошибка!\n");
    else if (pid == 0) {
      printf("Порождение процесса 2 PID = %d PPID = %d\n", getpid(),getppid());
      
      //порождение 4 цикла
        if ((pid = fork()) == -1)
          printf("Ошибка!\n");
        else if (pid == 0) {
          printf("Порождение 4 PID = %d PPID = %d\n", getpid(), getppid());
          printf("Завершился процесс 4: PID = %d, PPID = %d\n",getpid(), getppid());
          exit(0);
        } //else sleep(0.25);
      
      // Порождение 5 процесса
      if ((pid = fork()) == -1)
        printf("Ошибка!\n");
      else if (pid == 0) {
        printf("Порождение 5 PID = %d PPID = %d\n", getpid(), getppid());

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
        } else sleep(1);

        printf("Завершился процесс 5: PID = %d, PPID = %d\n",
          getpid(), getppid());
          exit(0);
      }else sleep(1.5);
      
      printf("Завершился процесс 2 PID = %d PPID = %d\n", getpid(),getppid());
      exit(0);
    }else sleep(1);

    
    printf("Завершился процесс 1: PID = %d, PPID = %d\n", getpid(),
      getppid());
    exit(0);
  } else sleep(4);
  //printf("Завершился процесс 0: PID = %d, PPID = %d\n", getpid(),
  //  getppid());
  return 0;
}
