#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>

/******************************************
*  函数名：main
*函数功能：向指定进程号的进程发送用户输入的信号
*输    入：要发送信号的目标进程号
*输    出：无
*  返回值：无
*修改日期：2017-03-15
*修改作者：zzj
*******************************************/
int main (int argc, char **argv)
{
	int keyboard;
	int ret,i;
	char c;
	fd_set readfd;
	struct timeval timeout;
	
	keyboard = open("/dev/tty",O_RDONLY | O_NONBLOCK);
	assert(keyboard>0);
	
	while(1)
	{
		timeout.tv_sec=1;
		timeout.tv_usec=0;
		FD_ZERO(&readfd);
		FD_SET(keyboard,&readfd);

		ret=select(keyboard+1,&readfd,NULL,NULL,&timeout);
		if(FD_ISSET(keyboard,&readfd))
		{
			i=read(keyboard,&c,1);
			if('\n'==c)
				continue;
			printf("your input is %c\n",c);
			
			/* 在进程处理的函数中定义了信号1-5的处理 */
			if (c >= '1' && c <= '5')
				kill(atoi(argv[1]), c - '1' + 1);
			
			if ('q'==c)
			{
				kill(atoi(argv[1]), SIGKILL);	/* SIGKILL为9 */
				break;
			}
		}
	}
}
