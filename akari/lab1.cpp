#include <bits/stdc++.h>
// # include "akari.h"

using namespace std;

namespace aka
{

typedef struct point
{
	int x;
	int y;
	int val;
} point;

point black[100];

int cover[8][8];
int type[8][8];
int map[8][8];
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

bool ok;

int n=0;
int m=0;

bool cmp(point A, point B)
{
	return A.val < B.val;
}

bool in_range(int x, int y)
{
	return (x >= 1 && y >= 1 && x <= n && y <= m);
}


int on(int x, int y)// put in (x,y)
{
	int ret=1; //light num
	int i = 0;
	int j = 0;
	for(int k=0;k<4;k++)
	{
		i=x+dx[k];
		j=y+dy[k];
		while (in_range(i,j)&& && type[i][j] != 2)
		{
			cover[i][j]++;
			if(cover[i][j] == 1)
				ret ++;
			i+=dx[k];
			j+=dy[k];
		}
	}
	return ret;
}

int off(int x,int y)
{
	int ret=1; //light num
	int i = 0;
	int j = 0;
	for(int k=0;k<4;k++)
	{
		i=x+dx[k];
		j=y+dy[k];
		while (in_range(i,j)&& && type[i][j] != 2)
		{
			cover[i][j]--;
			i+=dx[k];
			j+=dy[k];
		}
	}
	return ret;
}


int check_overlap()
{
	int i,j;
    int tmp;
    int ret = 2;
    for(i = 0;i < b;i++) // check black
    {
        if(black[i].val == -1)
            continue;
        tmp = 0;
        for(j = 0;j < 4;j ++)//check black neibor
        {
            int tx = black[i].x + dx[j];
            int ty = black[i].y + dy[j];
			if(!in_range(tx,ty))
			{
				continue;
			}
            if(type[tx][ty] == 3)
                tmp ++;
        }
        if(tmp > black[i].val)
            return 0;
        if(tmp != black[i].val)
            ret = 1;
    }
    return ret;
}

void dfs_for_black(int x,int y,int count,int depth)
{
	if(ok)
	{
		return ture;
	}
	if(count == m*n-b) //light all
	{
		ok=ture;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				map[i][j]=type[i][j];
			}
		}
	}
	for(int i = x;i <= n;i ++)
    {
        for(int j = 1;j <= m;j ++)
        {
            if(type[i][j] == 0 && cover[i][j] == 0)
            {
                type[i][j] = 3;
                if(check_overlap() != 2) //overlap
                {
                    type[i][j] = 0;
                    continue;
                }
                int light_num = on(i,j);
                dfs_for_black(i,j,count + light_num,depth + 1);
                off(i,j);
                type[i][j] = 0;
            }
        }
    }
	return false;
}

void dfs_for_white(int id,int count,int depth)
{
	if(ok)
	{
		return;
	}
	if(id == b)
    {
        if(check_overlap() == 2)// this situ should not
        {
			printf("AS");
            dfs_for_black(1,1,count,depth);
        }
        return;
    }
	int i=0;
	int j=0;
	for(i=0;i<4;i++) // chekc neibor
	{
		if(type[black[id].x + dx[i]][black[id].y + dy[i]] == 3)
            j++;
	}
	if(!in_range(i,j))
	{
		return;
	}
	else
    {
        if(j == black[id].val)
            dfs_for_white(id + 1,count,depth);
        else
        {
            for(i = 0;i < 4;i ++)
            {
                int tx = black[id].x + dx[i];
                int ty = black[id].y + dy[i];
                if(tx < 1 || ty < 1 || tx > n || ty > m)
                    continue;
                if(flag[tx][ty] == 0 && cover[tx][ty] == 0)
                {
                    flag[tx][ty] = 3;
                    if(check_overlap() == 0)
                    {
                        flag[tx][ty] = 0;
                        continue;
                    }
                    int tp = put(tx,ty);
                    dfs(id,cnt + tp,ca + 1);
                    deput(tx,ty);
                    flag[tx][ty] = 0;
                }
            }
        }
    }
}





vector<vector<int>> solveAkari(vector<vector<int>> &g) 
{

}

} // namespace aka


// int main()
// {
// 	return 0;
// }