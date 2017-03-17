#include <stdio.h>        
#include <sys/types.h>        
//#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int flag = 1; 

/******************************************
*  函数名：func
*函数功能：信号处理函数
*输    入：信号
*输    出：无
*  返回值：无
*修改日期：2017-03-15
*修改作者：zzj
*******************************************/
void func(int sig) 
{
	printf("I get a signal:%d\r\n", sig);
	flag = 1;
}

/******************************************
*  函数名：main
*函数功能：signal的入口，安装进程处理器
*输    入：无
*输    出：无
*  返回值：OK
*修改日期：2017-03-15
*修改作者：zzj
*******************************************/
int main()
{
	/* 给进程安装信号处理器 */
	signal(1, func);
	signal(2, func);
	signal(3, func);
	signal(4, func);
	signal(5, func);
	printf("pid:%ld\n",(long)getpid());

	sleep(10);	/* 等待10s */
	
	raise(3);		/* 向当前进程发送信号 */
	
	while(flag)
	pause();		/* 挂起当前进程，等待信号 */
	
	return 0;
}