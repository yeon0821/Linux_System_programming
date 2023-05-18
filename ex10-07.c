#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <st

void timeover(int signum)
{
		printf("\n\ntime over!!\n\n");
		exit(0);
}

main(){
	
	char buf[1024];
	char *alpha = "abcdefghijklmnopqrstuvwxyz";
	
	int timelimit;
	struct sigaction act;
	
	act.sa_hadler = timeover;
	sigaction(SIGALRM, &act, NULL);
	printf("input timelimit (sec)..\n");
	scanf("%d", &timelimit);

	alarm(timelimit);
	
	printf("START!!\n >");
	scanf("%s", buf);

	if(!strcmp(bug,alpha))
		printf("well done...\n");
	else
		printf("sorry...you fail!\n");

