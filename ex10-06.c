#include <unistd.h>
#include<signal.h>
#include <sys/types.h>

main() {

	pid_t pid;
	int count = 5;

	if((pid = fork()) > 0){
		
		sleep(2);
		kill(pid, SIGINT);
		raise(SIGINT);
		printf("[parent] bye 
