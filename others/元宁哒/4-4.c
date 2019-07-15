#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <string.h>
/*********Begin*********/
long long FBNQ(int n)
{
    return (pow((1+sqrt((double)5)),n)-pow((1-sqrt((double)5)),n))/(pow((double)2,n)*sqrt((double)5));
}
int main(int argv,char* argc[])
{
        int myid,numprocs,namelen;

        MPI_Status status;
        //char message[100];
        MPI_Init(&argv,&argc);
        MPI_Comm_rank(MPI_COMM_WORLD,&myid);
        MPI_Comm_size(MPI_COMM_WORLD, &numprocs);


        //char processor_name[MPI_MAX_PROCESSOR_NAME];
        int max_len=51;

        long long* message = (long long*)malloc(sizeof(long long)*max_len);
        long long* recv = (long long*)malloc(sizeof(long long)*max_len);
        memset(message, 0, max_len);
        memset(recv, 0, max_len);

        int loop = max_len/(numprocs-1);

        if(max_len%(numprocs-1) != 0)
                loop++;

        if(myid != 0) //非0号进程发送消息
        {
            for(int i = ( myid - 1 ) * loop; i < myid*loop; ++i)            
                message[i] = FBNQ(i);        

            MPI_Send(message, max_len, MPI_LONG_LONG_INT, 0, 0, MPI_COMM_WORLD);
        }
        else// myid == 0，即0号进程接收消息
        {
            int n = 0;
            scanf("%d", &n);
            for(int i = 1; i < numprocs; ++i)
            {
                MPI_Recv(recv, max_len, MPI_LONG_LONG_INT, i, 0, MPI_COMM_WORLD, &status);
                for(int j = (i-1)*loop; j < i*loop; ++j)
                    message[j] = recv[j];                
            }
            for(int i = 1; i < n; ++i)
                    printf("%lld ", message[i]);
            if (n != 1)            
                printf("%lld\n", message[n]);            
            else            
                printf("1\n");            

        }
        MPI_Finalize();
        return 0;
}
/*********End*********/