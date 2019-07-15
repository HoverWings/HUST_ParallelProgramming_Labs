#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

long a[100];
pthread_t pthread_t_pool[8];
int main()
{
    for(int i=0;i<8;i++)
    {

    }
    pthread_t p1,p2;
	int ret1,ret2;
	int i=0,n=0;
	union semun arg;
	scanf("%d",&n);
	getchar();
	sequence=(long long *)malloc((n+1)*sizeof(long long));
	sequence[0]=1;
	sequence[1]=1;
	semid=semget(IPC_PRIVATE,2,IPC_CREAT|0666);//创建信号量集
	arg.val=0;
	semctl(semid,0,SETVAL,arg);//赋值
	arg.val=1;
	semctl(semid,1,SETVAL,arg);
	ret1=pthread_create(&p1,NULL,subp1,(void *)&n);//创建线程
	ret2=pthread_create(&p2,NULL,subp2,(void *)&n);
	if(ret1||ret2)
	{
		printf("ERROR!\n");
		return;
	}
	pthread_join(p1,NULL);//挂起线程
	pthread_join(p2,NULL);
	semctl(semid,0,IPC_RMID,NULL);//释放
	semctl(semid,1,IPC_RMID,NULL);
	for(i=0;i<n-1;i++) printf("%lld ",sequence[i]);//打印结果
	printf("%lld\n",sequence[i]);
	return 0;
}

