#include <stdio.h>
#include <math.h>

/***** Begin *****/

__global__ static void fibo_cuda(long* result){
		int tid =threadIdx.x + 1;
        long num1 = 0,num2 = 1,num3 = 0;
    	if(tid==0)num3 = 0;
    	else if(tid==1)num3 = 1;
    	else{
            for(int i = 2;i <= tid;i++){
       	    num3 = num2 + num1;
            num1 = num2;
            num2 = num3;
         }
    	}     
    result[tid] = num3;
}
int main()
{
    long* result1;
    long result[51];
    int length;
    scanf("%d",&length);
    int N = sizeof(long)*(length+1);
    cudaMalloc((void **)&result1,N);
    fibo_cuda<<<1,length>>>(result1);
    cudaMemcpy(&result,result1,N,cudaMemcpyDeviceToHost);
    for(int j = 1;j <length;j++){
            printf("%ld ",result[j]);
        }
        printf("%ld\n",result[length]);
	return 0;
}
/***** End *****/
