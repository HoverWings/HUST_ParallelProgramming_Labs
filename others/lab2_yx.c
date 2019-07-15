#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <linux/sem.h>

void P(int semid,int index);
void V(int semid,int index);
void *subp1();
void *subp2();

long long *sequence;
int semid;



void P(int semid,int index)
{
  struct sembuf sem;
  sem.sem_num=index;
  sem.sem_op=-1;
  sem.sem_flg=0;//操作标记：0或IPC_NOWAIT等
  semop(semid,&sem,1);//1:表示执行命令的个数
  return;
}

void V(int semid,int index)
{
	struct sembuf sem;
	sem.sem_num=index;
	sem.sem_op=1;
	sem.sem_flg=0;
	semop(semid,&sem,1);
	return;
}


void *subp1(void * max)//偶数下标
{
	int n=*((int *)max);
	int i=0;
	for(i=2;i<=n;i=i+2)
	{
		P(semid,0);
		sequence[i]=sequence[i-1]+sequence[i-2];
		V(semid,1);
	}
}

void *subp2(void * max)//奇数下标
{
	int n=*((int *)max);
	int i=0;
	for(i=2;i<=n;i=i+2)
	{
		P(semid,1);
		sequence[i+1]=sequence[i-2]+sequence[i-1]+sequence[i-1];
		V(semid,0);
	}
}


int main(void)
{
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



