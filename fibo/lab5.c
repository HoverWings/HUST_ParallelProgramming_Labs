//CUDA
#include <stdio.h>
#include <math.h>
#define ll long long

__global__ static void fibo_cuda(long* result){
		int tid =threadIdx.x + 1;
        ll f1 = 0;
        ll f2 = 1;
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
            for(int i = 2;i <= tid;i++)
            {
       	        f3 = f2 + f1;
                f1 = f2;
                f2 = f3;
            }
    	}     
    result[tid] = num3;
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

    cudaMemcpy(&result,result1,N,cudaMemcpyDeviceToHost);
    for(int j = 1;j <n;j++)
    {
        printf("%lld ",result[j]);
    }
    printf("%lld\n",result[n]);
	return 0;
}