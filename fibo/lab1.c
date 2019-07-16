#include<stdio.h>
#define int long

int a[100];

int f(int i)
{
    if(a[i]!=-1)
    {
        return a[i];
    }
    else
    {
        if(i==0)
        {
            a[i]=0;
            return a[i];
        }
        if(i==1)
        {
            a[i]=1;
            return a[i];
        }
        if(i>1)
        {
            a[i]=f(i-1)+f(i-2);
            return a[i];
        }
    }
    
}


int main()
{
    //init
    for(int i=0;i<100;i++)
    {
        a[i]=-1;
    }

    int n;
    scanf("%ld",&n);
    for(int i=1;i<n+1;i++)
    {
        printf("%ld",f(i));
        if(i!=(n))
        {
            printf(" ");
        }
    }
    printf("\n");
	return 0;
}
