#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
int fd = -1;
void init_testlog()
{
	if(fd != -1 ){ close(fd);fd =-1;}
	
	fd = open("test.log", O_CREAT|O_WRONLY|O_TRUNC , 0777);
	if (fd != -1) return ;
	
	printf("%s_%s_%d: fail to create log file\n"
			, __FILE__, __func__, __LINE__);
}

void deinit_testlog()
{
	if (fd == -1) return;
	close(fd);
}

void log_pr(const char *fmt,...)
{
	char buf[128] = {};
	va_list argp;
	va_start(argp,fmt);
	vsprintf(buf, fmt, argp);
	va_end(argp);
	write(fd, buf, strlen(buf));
	fsync(fd);

}
