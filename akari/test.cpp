#include<stdio.h>


int main()
{
    int solution4[1][4] = {{1,1,1,1}};
    int solution3[4][4] = {{0,1,1,1},{1,0,1,1},{1,1,0,1},{1,1,1,0}};
    int solution2[6][4] = {{1,1,0,0},{1,0,1,0},{0,1,1,0},{0,1,0,1},{0,0,1,1},{1,0,0,1}};
    int solution1[4][4] = {{0,0,1,0},{0,0,0,1},{0,1,0,0},{1,0,0,0}};
    int solution0[1][4] = {{0,0,0,0}};
    int** solution[5]={(int **)solution4,(int **)solution3,(int **)solution2,(int **)solution1,(int **)solution0};
    int a= solution[0][0][0];
    return 0;
}