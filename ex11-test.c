#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define MESSAGE_SIZE 100 // 메시지의 최대 크기

int main() {
    int pipe1[2]; // 파이프 1
    int pipe2[2]; // 파이프 2

    pid_t pid1, pid2; // 자식 프로세스의 ID

    // 파이프 생성
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("파이프 생성 오류");
        exit(1);
    }

    // 첫 번째 자식 프로세스 생성
    pid1 = fork();
    if (pid1 == -1) {
        perror("프로세스 생성 오류");
        exit(1);
    } else if (pid1 == 0) {
        // 자식 프로세스 1

        close(pipe1[1]); // 파이프 1의 쓰기 단을 닫음
        close(pipe2[0]); // 파이프 2의 읽기 단을 닫음

        char message[MESSAGE_SIZE];
        // 파이프 1에서 메시지를 읽어옴
        read(pipe1[0], message, MESSAGE_SIZE);
        printf("자식 프로세스 1: 받은 메시지 - %s\n", message);

        // 받은 메시지에 "Process 1: "을 추가한 후 파이프 2로 메시지를 전달
        strcat(message, " Process 1");
        write(pipe2[1], message, strlen(message) + 1);

        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    }

    // 두 번째 자식 프로세스 생성
    pid2 = fork();
    if (pid2 == -1) {
        perror("프로세스 생성 오류");
        exit(1);
    } else if (pid2 == 0) {
        // 자식 프로세스 2

        close(pipe1[0]); // 파이프 1의 읽기 단을 닫음
        close(pipe2[1]); // 파이프 2의 쓰기 단을 닫음

        char message[MESSAGE_SIZE];
        // 파이프 2에서 메시지를 읽어옴
        read(pipe2[0], message, MESSAGE_SIZE);
        printf("자식 프로세스 2: 받은 메시지 - %s\n", message);

        // 받은 메시지에 "Process 2: "을 추가한 후 파이프 1로 메시지를 전달
        strcat(message, " Process 2");
        write(pipe1[1], message, strlen(message) + 1);

        close(pipe1[1]);
        close(pipe2[0]);
        exit(0);
    }

    // 부모 프로세스

    close(pipe1[0]); // 파이프 1의 읽기 단을 닫음
    close(pipe2[0]); // 파이프 2의 읽기 단을 닫음
    close(pipe2[1]); // 파이프 2의 쓰기 단을 닫음

    char message[MESSAGE_SIZE] = "Hello, World!";
    printf("부모 프로세스: 보낼 메시지 - %s\n", message);

    // 부모 프로세스에서 파이프 1을 통해 메시지를 전달
    write(pipe1[1], message, strlen(message) + 1);

    // 자식 프로세스들이 작업을 마치기를 기다림
    wait(NULL);
    wait(NULL);

    // 파이프 닫기
    close(pipe1[1]);

    exit(0);
}

