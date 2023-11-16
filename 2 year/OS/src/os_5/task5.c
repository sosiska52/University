#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1000

int countWords(char* line) {
    int count = 0;
    char* token = strtok(line, " ");
    while (token != NULL) {
        int fd;
        char filename[50];
        char data[50];
        count++;

        size_t length = strlen(token);
        //(void)umask(0);
        snprintf(filename, sizeof(filename), "%zu.txt", length);
        if ((fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666)) < 0) {
            printf("Can't open file\n");
            exit(-1);
        }
        size_t size = write(fd, token, length);
        char newLine = '\n';
        size = write(fd, &newLine, 1);
        if (close(fd) < 0) {
            printf("Can't close\n");
            exit(-1);
        }
        token = strtok(NULL, " ");

    }
    return count;
}

void filterLines(FILE* file) {
    char line[MAX_LINE_LENGTH];
    int counter = 0;
    while (fgets(line, sizeof(line), file)) {
        counter++;
        if (countWords(line) > 3) {
            printf("%d ", counter);
        }
    }
}

int main() {
    // Фильтрация и вывод строк с более чем 3 словами
    filterLines(stdin);
    printf("\n");
    return 0;
}
