#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
/*********Begin*********/
struct Data{
     int num; //斐波那契数列的项数
     long long* list;
}data;
long long Fib(void *data)
{
    struct Data *tmp = (struct Data*)data;
    double gh5=sqrt((double)5);
    tmp->list[tmp->num] = (pow((1+gh5),tmp->num)-pow((1-gh5),tmp->num))/(pow((double)2,tmp->num)*gh5);
}
int main(){
    int ret;
    int n;
    int i;
    scanf("%d",&n);
    if(n == 1)
    {
        printf("1\n");
        return 0;
    }
    struct Data* data = (struct Data*)malloc(sizeof(struct Data)*n);
    pthread_t* th_list = (pthread_t*)malloc(sizeof(pthread_t)*n);
    long long* result = (long long*)malloc(sizeof(long long)*(n+1));
    for(int i = 1; i <= n; ++i)
    {
        data[i-1].num = i;
        data[i-1].list = result;
       ret = pthread_create(&th_list[i-1], NULL, Fib, (void *)&data[i-1]);
    }
    for(int i = 0; i < n; ++i)
        pthread_join( th_list[i], NULL);
    for(int i = 1; i < n; ++i)
    {
       printf("%lld ", result[i]);
    }
    printf("%lld\n", result[n]);
    free(data);
    free(th_list);
    free(result);
    return 0;
}
/**********End*********/