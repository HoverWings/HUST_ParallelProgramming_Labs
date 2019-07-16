#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#define ll long long
ll a[100];
int n=0;
int thread_num=16;


void* par_fun(void * tn)
{
	// int tn=*((int *)tn);
    int par_tn=*((pthread_t *)tn);
    // printf("par_tn:%d\n",par_tn);
	for(int i=par_tn;i<=n+1;i+=thread_num)
	{
		a[i]=(long)(1.0/sqrt(5.0)*(pow((1.0+sqrt(5.0))/2.0,i)-pow((1.0-sqrt(5.0))/2.0,i)));
	}
}



int main()
{
	scanf("%d",&n);
    // thread_num=(int)(n/2+0.5);
    pthread_t threads[thread_num];
    int tn;
    for(tn=0;tn<thread_num;tn++)
    {
        pthread_create(&threads[tn],NULL,par_fun,(void *)&tn);
        usleep(20);
    }
    for(tn=0;tn<thread_num;tn++)
    {
        pthread_join(threads[tn],NULL);
    }
	for(int i=1;i<n;i++)
	{
		printf("%lld ",a[i]);
	}
    printf("%lld\n",a[n]);
    return 0;
}

