/* Sébastien Boisvert */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>

void handler(int signal){
}

int main(int argc,char**argv){

/* register signal action */
	struct sigaction new_action;
	new_action.sa_handler=handler;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags=SA_RESTART;

	sigaction(SIGALRM,&new_action,NULL);

/* register timer for sending SIGALRM */
	struct itimerval value, ovalue;
	value.it_interval.tv_sec = 0;
	value.it_interval.tv_usec = 1000;
	value.it_value.tv_sec = 0;
	value.it_value.tv_usec = 2000;
	
	setitimer(ITIMER_REAL, &value, &ovalue );

/* do a lot of IOPS */
	FILE*fp=fopen("data","w");

	if(errno==EINTR)
		printf("EINTR for fopen\n");


	int i=0;
	while(i<1024*1024*1024){
		fwrite(&i,sizeof(int),1,fp);

		if(errno==EINTR)
			printf("EINTR for fwrite\n");

		fflush(fp);

		if(errno==EINTR)
			printf("EINTR for fflush\n");
	
		i++;
	}

	fclose(fp);

	if(errno==EINTR)
		printf("EINTR for fclose\n");

	return EXIT_SUCCESS;
}
