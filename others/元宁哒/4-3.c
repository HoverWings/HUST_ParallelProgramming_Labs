#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
/***** Start *****/
long Fib(int n)
{
    double gh5=sqrt((double)5);
    return (pow((1+gh5),n)-pow((1-gh5),n))/(pow((double)2,n)*gh5);
}
int main(void){
    int n;
    scanf("%d",&n);
    long index[n+1];
    int arr[n];
    #pragma omp parallel for
    for (int i = 1; i <=n; i++) {
        index[i] = Fib(i);
    }
    for (int i = 1;i<n;i++){
        printf("%ld ",index[i]);
    }
    printf("%ld\n",index[n]);
}