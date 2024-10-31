#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdbool.h>

bool est_premier(int n)
{
	if(n <= 1) return false;
	if(n == 2) return true;
	if(n % 2 == 0) return false;
	for(int i = 3; i * i <= n; i += 2)
	{
		if (n % i == 0) return false;
	}

	return true;
}






int main(int argc, char *argv[])
{
  int nombre = atoi(argv[1]);
  int fd[2];
  int retourFd[2];
  int pipe_result = pipe(fd);
  if(pipe_result == -1)
  {
	  perror("pipe");
	  return 1;
  }

  if(nombre <= 0)
  {
	  printf("Le nombre de depart doit etre positif.\n");
  }

  if(pipe(fd) == -1 || pipe(retourFd) == -1)
  {
	  perror("pipe");
	  return 1;
  }

  


  pid_t pid = fork();
  if(pid == -1)
  {
	  perror("pid");

	  return 1;
  }



  if(pid > 0)
  {
	  close(fd[0]);
	  close(retourFd[1]);

	  for(int i = nombre; i >= 0; i--)
	  {
		  write(fd[1], &i, sizeof(i));
		  sleep(1);

		  char message[50];
		  read(retourFd[0], message, sizeof(message));
		  printf("Parent a recu : %d -> %s\n", i, message);
	  }


	  close(fd[1]);
	  close(retourFd[0]);
	  wait(NULL);
  }else
  {
	  close(fd[1]);
	  close(retourFd[0]);
	  int count;
	  while(read(fd[0], &count, sizeof(count)) > 0)
	  {
		  char result[50];

		  if(count % 2 == 0){

		  if(count == 2 || est_premier(count))
		  {
			  sprintf(result, "pair et premier");
		  }else
		  {
			  sprintf(result, "pair");
		  }
		 }
		  else{
			  if(est_premier(count))
			  {
				  sprintf(result, "impaire et premier");
			  } else{
				  sprintf(result, "impair");
			  }
		  }

	   write(retourFd[1], result, sizeof(result));
	  }

	  close(fd[0]);
	  close(retourFd[1]);
  }

  return 0;

}
