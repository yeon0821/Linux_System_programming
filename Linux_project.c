#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_BLOCKS 10
#define MAX_PARAMETERS 3

struct swInfo {
    char name[20];
    char restart_count[20];
    char start_time[20];
    char reason[20];
};

typedef struct swParam {
    char SwBlock[20];
    char App_params[MAX_PARAMETERS][20];
} swParam;

typedef struct _swInfoManager {
    pid_t pids[MAX_BLOCKS];
    pid_t dpid;
    int p_no;
    struct swInfo sw_info[MAX_BLOCKS];
    struct swParam sw_param[MAX_BLOCKS];
} swManager;

void readFileList(void) {
    FILE* file = fopen("sw_block_info.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ";");

        strcpy(swManager.sw_info[swManager.p_no].name, token);
        strcpy(swManager.sw_info[swManager.p_no].restart_count, strtok(NULL, ";"));
        strcpy(swManager.sw_info[swManager.p_no].start_time, strtok(NULL, ";"));
        strcpy(swManager.sw_info[swManager.p_no].reason, strtok(NULL, ";"));

        swManager.p_no++;
    }

    fclose(file);
}

void InitSWBlock(swManager* info, FILE* log_file) {
    for (int i = 0; i < info->p_no; i++) {
        pid_t pid = fork();
        if (pid > 0) {
            info->pids[i] = pid;
            strcpy(info->sw_info[i].start_time, "Initialized");
            fprintf(log_file, "Process %s initialized with PID: %d\n", info->sw_info[i].name, pid);
        } else if (pid == 0) {
            execl(info->sw_info[i].name, info->sw_info[i].name, NULL);
            exit(0);
        } else {
            fprintf(log_file, "Failed to fork process for %s\n", info->sw_info[i].name);
        }
    }
}

void restartProcess(swManager* info, int index) {
    pid_t pid = fork();
    if (pid > 0) {
        info->pids[index] = pid;
        strcpy(info->sw_info[index].start_time, "Restarted");
    } else if (pid == 0) {
        exit(0);
    }
}

void LogInterface(FILE* fp, const swManager* info) {
    system("clear");

    for (int i = 0; i < info->p_no; i++) {
        fprintf(fp, "S/W Block Name: %s\n", info->sw_info[i].name);
        fprintf(fp, "Restart Count: %s\n", info->sw_info[i].restart_count);
        fprintf(fp, "Start Time: %s\n", info->sw_info[i].start_time);
        fprintf(fp, "Reason: %s\n", info->sw_info[i].reason);
        fprintf(fp, "PID: %d\n", info->pids[i]);
        fprintf(fp, "---------------------------------------\n");
    }

    rewind(fp);
    char c;
    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
    }
}

int main() {
    swManager swManager;
    FILE* log_file = fopen("log.txt", "w+");
    if (log_file == NULL) {
        printf("Error opening log file.\n");
        return 1;
    }

    readFileList();

    InitSWBlock(&swManager, log_file);

    LogInterface(log_file, &swManager);

    while (1) {
        pid_t pid = waitpid(-1, NULL, WNOHANG);
        if (pid > 0) {
            swManager.dpid = pid;

            for (int i = 0; i < swManager.p_no; i++) {
                if (swManager.pids[i] == pid) {
                    fprintf(log_file, "Process %s with PID %d has terminated. Restarting...\n", swManager.sw_info[i].name, pid);
                    restartProcess(&swManager, i);
                    break;
                }
            }
        }

        sleep(5);
        LogInterface(log_file, &swManager);
    }
}
