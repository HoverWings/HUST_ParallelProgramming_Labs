#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

long a[100];

int main()
{
	int n=0;
	omp_set_num_threads(2);
	scanf("%d",&n);
	getchar();
	a[0]=1;
	a[1]=1;
	#pragma omp parallel for
	for(int i=2;i<n;i++)
	{
		a[i]=a[i-1]+a[i-2];
	}
	for(int i=0;i<n-1;i++)
    {
        printf("%lld ",a[i]);
    }
	printf("%lld\n",a[n-1]);
	return 0;
}
