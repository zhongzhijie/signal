#include <stdio.h>        
#include <sys/types.h>        
//#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int flag = 1; 

/******************************************
*  ��������func
*�������ܣ��źŴ�����
*��    �룺�ź�
*��    ������
*  ����ֵ����
*�޸����ڣ�2017-03-15
*�޸����ߣ�zzj
*******************************************/
void func(int sig) 
{
	printf("I get a signal:%d\r\n", sig);
	flag = 1;
}

/******************************************
*  ��������main
*�������ܣ�signal����ڣ���װ���̴�����
*��    �룺��
*��    ������
*  ����ֵ��OK
*�޸����ڣ�2017-03-15
*�޸����ߣ�zzj
*******************************************/
int main()
{
	/* �����̰�װ�źŴ����� */
	signal(1, func);
	signal(2, func);
	signal(3, func);
	signal(4, func);
	signal(5, func);
	printf("pid:%ld\n",(long)getpid());

	sleep(10);	/* �ȴ�10s */
	
	raise(3);		/* ��ǰ���̷����ź� */
	
	while(flag)
	pause();		/* ����ǰ���̣��ȴ��ź� */
	
	return 0;
}