#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid = fork();
	
	if (pid > 0)
	{
		sleep(5);
		printf("i am the parent process and my child pid is %d\n", pid);
	}
	else if(pid == 0)
	{
		printf("i am the child process and my parent pid is %d\n", getppid());
	}
	else if(pid == -1)
	{
		perror("fork failed\n");
	}

	if (pid > 0)
	{
		return 1;
	}

	int status = 0;
	pid = wait(&status);
	
	if (WIFEXITED(status))
	{
		printf("normal termination with exit status = %d\n", WEXITSTATUS(status));
	}

	if (WIFSIGNALED(status))
	{
		printf("killed by signal = %d\n", WTERMSIG(status));
	}

	if (WIFSTOPPED(status))
	{
		printf("Stopped by signal = %d\n", WSTOPSIG(status));
	}

	if (WIFCONTINUED(status))
	{
		printf("Continued\n");
	}

	return 0;
}
