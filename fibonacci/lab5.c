//CUDA
#include <stdio.h>
// #include <math.h>
#define ll long long

ll F(int n)
{
    return (ll)(1.0/sqrt(5.0)*(pow((1.0+sqrt(5.0))/2.0,n)-pow((1.0-sqrt(5.0))/2.0,n)));
}

__global__ static void fibo_cuda(ll* result){
    int tid =threadIdx.x + 1;
    ll f3 = 0;
    if(tid==0)
    {
        f3 = 0;
    }
    else if(tid==1) // print from 1
    {
        f3 = 1;
    }
    else
    {
        ll n=tid;
        f3=(ll)(1.0/sqrt(5.0)*(pow((1.0+sqrt(5.0))/2.0,(double)n)-pow((1.0-sqrt(5.0))/2.0,(double)n)));
    }     
    result[tid] = f3;
}


int main()
{
    ll* p_result;
    ll result[100];
    int n;
    scanf("%d",&n);
    int N = sizeof(long)*(n+1); //add zero to the arr
    cudaMalloc((void **)&p_result,N);

    fibo_cuda<<<1,n>>>(p_result);

    cudaMemcpy(&result,p_result,N,cudaMemcpyDeviceToHost);
    for(int j = 1;j <n;j++)
    {
        printf("%lld ",result[j]);
    }
    printf("%lld\n",result[n]);
	return 0;
}