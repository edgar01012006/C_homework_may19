#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int log_base_two(int num) {
	int cnt = 0;
	while (num != 1) {
		num /= 2;
		++cnt;
	}
	return cnt;
}

int factorial(int num) {
	int res = 1;
	for (int i = 1; i < num; ++i) {
		res *= i;
	}
	return res;
}

int cube(int num) {
	return num * num * num;
}

int main() {
	pid_t pid1, pid2, pid3;
	int num = 0;
	scanf("%d", &num);	

	pid1 = fork();
	if (pid1 == 0) {
		log_base_two(num);
		exit(0);
	}
	
	pid2 = fork();
	if (pid2 == 0) {
		factorial(num);
		exit(0);
	}
	
	pid3 = fork();
	if (pid3 == 0) {
		cube(num);
		exit(0);
	}

	pid_t first_finished_pid = waitpid(-1, NULL, 0);
	if (first_finished_pid > 0) {
		printf("First finished process's pid is = %d\n", first_finished_pid);
		
		if (first_finished_pid != pid1) kill(pid1, SIGKILL);
        	if (first_finished_pid != pid2) kill(pid2, SIGKILL);
        	if (first_finished_pid != pid3) kill(pid3, SIGKILL);
	
	}

	return 0;
}
