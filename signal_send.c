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
*  ��������main
*�������ܣ���ָ�����̺ŵĽ��̷����û�������ź�
*��    �룺Ҫ�����źŵ�Ŀ����̺�
*��    ������
*  ����ֵ����
*�޸����ڣ�2017-03-15
*�޸����ߣ�zzj
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
			
			/* �ڽ��̴���ĺ����ж������ź�1-5�Ĵ��� */
			if (c >= '1' && c <= '5')
				kill(atoi(argv[1]), c - '1' + 1);
			
			if ('q'==c)
			{
				kill(atoi(argv[1]), SIGKILL);	/* SIGKILLΪ9 */
				break;
			}
		}
	}
}
