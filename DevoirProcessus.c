#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>


int main()
{
	
	pid_t pid;
	pid = fork();
	
        sleep(5);
	printf("Le parent envoie le Sigkill a l'enfant");

	kill(pid,SIGKILL);

	wait(NULL);
	printf("L'enfant a ete tuer");


	return 0;
}
