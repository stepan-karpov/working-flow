#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
  printf("Parent Id is %d\n", getpid());
	int x = 0;
	pid_t pid = fork();
	if (pid == 0) {
    // child
    printf("I am child! My id is %d, parent  id is %d\n", getpid(), getppid());
  } else {
    // parent
    wait(NULL);
    printf("I am parent!\n");
	}

	// scanf("%d", &x);

	return 0;
}
