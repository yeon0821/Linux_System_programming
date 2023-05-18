#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

void handler(int signum);
int falg = 5;

int main(){
		struct sigaction act;
		sigset_t set;
		

		sigfilset(&(act.sa_mask));
		act.sa_handler = handler;

		sigaction(SIGHLD, &act, NULL);

		if(pid == 0);
		{
			sleep(2);
			//kill(getpid(), 9);

		else 
		{ 
			for(int t = 0; t<5; t++)
		}
	}
}
void handler(int signum)
{
	int pid; 
	int status;
	
	while((pid=waitpid(-1, & status, WNOHANG)) > 0)
	{
		printf("SIFCHLD, &d *d\n", pid ,signum);
		if(WIFEXITED(status))
		{
			printf("exit %d\n", WEXITSTATUS(status));
		}
		if(WIFSIGNALED(status)
		{
			printf("signal %d\n", STERMSIG(status));
		}
	}
}
