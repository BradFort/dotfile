#include<stdio.h>
#include<unistd.h>


int main()
{
	int fd[2];
	int pipe_result = pipe(fd);
	if(pipe_result == -1)
	{
		perror("pipe");
		return 1;
	}

	pid_t pid = fork();

	if(pid == -1)
	{
		perror("fork");
		return 1;
	}

	if(pid == 0)
	{
		close(fd[0]);
		write(fd[1], "Hello\n", 6);
		close(fd[1]);
	} else  
	{
		close(fd[1]);
		char buffer[7];
		read(fd[0], buffer, 6);

		close(fd[0]);

		printf("Message rreecu :%s", buffer);
	}
}
