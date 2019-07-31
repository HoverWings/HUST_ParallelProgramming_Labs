//Serial
#include<stdio.h>
#include<time.h>
// #define int long
#define ll long long

ll a[100];

ll f(int i)
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


int main(int argc,char *argv[])
{
    //init
    clock_t start,finish;
    start = clock();
    for(int i=0;i<100;i++)
    {
        a[i]=-1;
    }
    int n=0;
    // sscanf(argv[1], "%d", &n);
    scanf("%d",&n);
    for(int i=1;i<n+1;i++)
    {
        printf("%lld",f(i));
        if(i!=(n))
        {
            printf(" ");
        }
    }
    printf("\n");
    finish=clock();
    double duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "%f seconds\n", duration );
    return 0;
}
