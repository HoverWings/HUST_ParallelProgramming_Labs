//MPI
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <string.h>
#define ll long long

ll F(int n)
{
    return (ll)(1.0/sqrt(5.0)*(pow((1.0+sqrt(5.0))/2.0,i)-pow((1.0-sqrt(5.0))/2.0,i)));
}
int main(int argv,char* argc[])
{
    int n = 0;
    int max_len=100;
    scanf("%d", &n);
    int process_id=0;
    int process_num=0;

    MPI_Status status;
    MPI_Init(&argv,&argc);
    MPI_Comm_rank(MPI_COMM_WORLD,&process_id);
    MPI_Comm_size(MPI_COMM_WORLD, &process_num);

    ll* message = (ll*)malloc(sizeof(ll)*max_len);
    ll* recv = (ll*)malloc(sizeof(ll)*max_len);
    memset(message, 0, max_len);
    memset(recv, 0, max_len);

    int loop = ceil(max_len/(process_num-1));
    if(process_id != 0) // send message
    {
        for(int i = ( process_id - 1 ) * loop; i < process_id*loop; ++i)    
        {
            message[i] = F(i);   
        }
        MPI_Send(message, max_len, MPI_LONG_LONG_INT, 0, 0, MPI_COMM_WORLD);
    }
    else//receive message
    {
        
        for(int i = 1; i < process_num; ++i)
        {
            MPI_Recv(recv, max_len, MPI_LONG_LONG_INT, i, 0, MPI_COMM_WORLD, &status);
            for(int j = (i-1)*loop; j < i*loop; j++)
            {
                message[j] = recv[j];  
            }                  
        }
        for(int i = 1; i < n; ++i)
        {
            printf("%lld ", message[i]);
        }
        if (n != 1)            
            printf("%lld\n", message[n]);            
        else            
            printf("1\n");            

    }
    MPI_Finalize();
    return 0;
}
