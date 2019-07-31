//OpenMp
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define ll long long
ll a[100];

ll F(int n)
{
    return (ll)(1.0/sqrt(5.0)*(pow((1.0+sqrt(5.0))/2.0,n)-pow((1.0-sqrt(5.0))/2.0,n)));
}

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
		a[i]=F(i);
	}
	for(int i=0;i<n-1;i++)
    {
        printf("%lld ",a[i]);
    }
	printf("%lld\n",a[n-1]);
	return 0;
}
