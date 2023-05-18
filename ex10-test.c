#include <unistd.h>

int main(){

	pid_t pid;
	
	if((pid = fork()) > 0)
	{
		printf("[parent] hello\n");
		pause();
		printf("[parent] bye!\n");
	}
	else if (pid == 0)
	{
	 
		printf("[child] hello\n");
		sleep(1);
		kill(getppid(), SIGINT);
		printf("[child] bye\n");
	}
	else 
		printf("fail to fork\n");
}
