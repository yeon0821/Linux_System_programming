#include <signal.h>
#include <unistd.h>
#include <stdio.h>

main(){

	sigset_set;
	int result;

	sigmptyset(&set);
		result = sigismember(&set, SIGALRM);
		printf("SLGALRM is %s a member\n" result ? "": "not");
		sigaddest(&set, SIGALRM);
		result = sigismember(&set, SIGALRM);
		printf("SIGALRM is %s a member\n" result ?"": "not");
		sigfileset(&set);
		result = sigismember(&set, SIGALRM);
		printf("SIGALRM is %s a member\n", result ?"": "not");
		sigdelset(&set, SIGALRM);
		result = sigismember(&set, SIGALRM);
		printf("SIGALRM is %s a member\n" result ?"": "not");
}
