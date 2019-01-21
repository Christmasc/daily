#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <wait.h>

int system_command(const char * cmd)
{
	pid_t pid;
	int ret;

	if ((pid = vfork()) < 0) {
		ret = -1;
	} else if (pid == 0) {
		execl("/bin/sh", "sh", "-c", cmd, NULL);
		_exit(127);
	} else {
		while (waitpid(pid, &ret, 0) < 0) {
			if (errno != EINTR) {
				ret = -1;
				break;
			}
		}
	}

	return ret;
}

int main(int argc, const char *argv[])
{
	int ret = 0;
	char cmd[32];

	sprintf(cmd, "ls -la");

	ret = system_command(cmd);
	if (ret == -1) {
		printf("command fail\n");
	} else {
		printf("command success\n");
	}
	return 0;
}
