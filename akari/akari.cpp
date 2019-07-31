// 文件由若干行组成，第一行为两个整数 n，m，代表棋盘的行数和列数。
// 之后的 n 行每行有 m 个整数表示棋盘的每个格子的状态，若它为 -2，则表示是白格子，若它为 -1，则表示是没有数字的黑格子，
// 若它为 0-4，则表示是数字 0-4 的黑格子。若你想把灯泡放在白色格子上面，则需要将 -2 改为 5，因为 5 表示有灯泡的格子。
#include <bits/stdc++.h>
#include "akari.h"
using namespace std;

//save the result
vector<vector<int> > result;
int get_result = 0;


namespace aka{


int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
int step[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
int solution4[1][4] = {{1,1,1,1}};
int solution3[4][4] = {{0,1,1,1},{1,0,1,1},{1,1,0,1},{1,1,1,0}};
int solution2[6][4] = {{1,1,0,0},{1,0,1,0},{0,1,1,0},{0,1,0,1},{0,0,1,1},{1,0,0,1}};
int solution1[4][4] = {{0,0,1,0},{0,0,0,1},{0,1,0,0},{1,0,0,0}};
int solution0[1][4] = {{0,0,0,0}};


struct point
{
    int x, y;
    int val;
};
//    vector<struct point> blacks;

bool cmp(const struct point &A, const struct point &B)
{
    return A.val < B.val;
}

void print_g(vector<vector<int> > g)
{
    printf("\n");
    for (int i=0; i<g.size(); i++)
    {
        for (int j=0; j<g.at(i).size(); j++)
        {
            printf("%2d ", g.at(i).at(j));
        }
        printf("\n");
    }
}

// can add light beside the point
bool can_add_light(vector<vector<int> > g, int x, int y)
{
    if (x < 0 || y < 0 || x>=g.size() || y>=g.at(0).size())// beside the wall
        return true;
    int max_count = g.at(x).at(y);
    if (max_count<0)
        return true;
    int now_count = 0;
    if (y+1<g.at(x).size() && g.at(x).at(y+1)>=5)
        now_count++;
    if (x+1<g.size() && g.at(x+1).at(y)>=5)
        now_count++;
    if (y-1>=0 && g.at(x).at(y-1)>=5)
        now_count++;
    if (x-1>=0 && g.at(x-1).at(y)>=5)
        now_count++;
    return ++now_count <= max_count;
}


bool in_range(vector<vector<int> > & g,int x, int y)
{
	return !(x < 0 || y < 0 || x>=g.size() || y>=g.at(0).size());
}



//判断(x,y)能否放一个灯泡，可以则放置
bool light_up(vector<vector<int> > & g, int x, int y, int flag)
{
    if(!in_range(g,x,y))
    {
        return false;
    }
    else if (g.at(x).at(y) >= 5) //already light
    {
        return true;
    }
    else if (g.at(x).at(y) > -2) //wall
    {
        return false;
    }
    else
    {
        //判断灯泡的上下左右格子能否容纳新增加的灯泡
        if (can_add_light(g, x, y+1) 
        && can_add_light(g, x, y-1)
        && can_add_light(g, x-1, y)
        && can_add_light(g, x+1, y))
        {
            //判断是否有灯泡互相照亮
            //上
            for (int i=x-1; i>=0; i--)
                if (g.at(i).at(y)>=-1 && g.at(i).at(y)<=4)//碰到墙
                    break;
                else if (g.at(i).at(y) >= 5)
                    return false;
            //下
            for (int i=x+1; i<g.size(); i++)
                if (g.at(i).at(y)>=-1 && g.at(i).at(y)<=4)//碰到墙
                    break;
                else if (g.at(i).at(y) >= 5)
                    return false;
            //左
            for (int i=y-1; i>=0; i--)
                if (g.at(x).at(i)>=-1 && g.at(x).at(i)<=4)//碰到墙
                    break;
                else if (g.at(x).at(i) >= 5)
                    return false;
            //右
            for (int i=y+1; i<g.at(x).size(); i++)
                if (g.at(x).at(i)>=-1 && g.at(x).at(i)<=4)//碰到墙
                    break;
                else if (g.at(x).at(i) >= 5)
                    return false;
            g.at(x).at(y) = flag;
            return true;
        }
        return false;
    }
    return false;
}

//if all whites are light on
bool is_ok(vector<vector<int> > g, vector<struct point> whites) 
{
    for (int i = 0; i < whites.size(); i++) 
    {
        if (g.at(whites[i].x).at(whites[i].y) == -2)
        {
            return false;
        }
    }
    return true;
}


void light_on_line(vector<vector<int> > &g,int x, int y)
{
    for (int k=x+1; k<g.size(); k++)
    {
        if (g.at(k).at(y)>=-1 &&  g.at(k).at(y)<=4)
            break;
        else
            g.at(k).at(y) = -3;
    }
    for (int k=x-1; k>=0; k--)
    {
        if (g.at(k).at(y)>=-1 &&  g.at(k).at(y)<=4)
            break;
        else
            g.at(k).at(y) = -3;
    }
    for (int k=y+1; k<g.at(x).size(); k++)
    {
        if (g.at(x).at(k)>=-1 &&  g.at(x).at(k)<=4)
            break;
        else
            g.at(x).at(k) = -3;
    }
    for (int k=y-1; k>=0; k--)
    {
        if (g.at(x).at(k)>=-1 &&  g.at(x).at(k)<=4)
            break;
        else
            g.at(x).at(k) = -3;
    }
}

void light_init(vector<vector<int> > &g)
{
    for (int i=0; i<g.size(); i++)
    {
        for (int j=0; j<g[i].size(); j++)
        {
            if (g.at(i).at(j) >= 5) //already light here
            {
                for (int k=i+1; k<g.size(); k++)
                {
                    if (g.at(k).at(j)>=-1 &&  g.at(k).at(j)<=4)
                        break;
                    else
                        g.at(k).at(j) = -3;
                }
                for (int k=i-1; k>=0; k--)
                {
                    if (g.at(k).at(j)>=-1 &&  g.at(k).at(j)<=4)
                        break;
                    else
                        g.at(k).at(j) = -3;
                }
                for (int k=j+1; k<g.at(j).size(); k++)
                {
                    if (g.at(i).at(k)>=-1 &&  g.at(i).at(k)<=4)
                        break;
                    else
                        g.at(i).at(k) = -3;
                }
                for (int k=j-1; k>=0; k--)
                {
                    if (g.at(i).at(k)>=-1 &&  g.at(i).at(k)<=4)
                        break;
                    else
                        g.at(i).at(k) = -3;
                }
            }
        }
    }
}


void light_off_line(vector<vector<int> > &g,vector<struct point> whites)
{
    // off all
    for (int i = 0; i < whites.size(); i++) 
    {
        if (g.at(whites[i].x).at(whites[i].y) == -3)
        {
            g.at(whites[i].x).at(whites[i].y) = -2;
        }
    }
    // light again
    light_init(g);
}

// the n-th white
bool back_tracking2(vector<vector<int> > g, vector<struct point> whites, int n)
{
    if (n == whites.size())
    {
        if (is_ok(g, whites))
        {
            result.resize(g.size());// copy result
            result.assign(g.begin(),g.end());
            get_result = 1;
            return true;
        }
        else// get the final state 
        {
            return false;
        }
    }
    struct point tmp;
    tmp = whites[n];
    int val = g.at(tmp.x).at(tmp.y);
    if (val == -2) //white point
    {
        if (light_up(g, tmp.x, tmp.y, 5)) // can put light
        {
            g.at(tmp.x).at(tmp.y) = 5;
            light_on_line(g,tmp.x, tmp.y);
            if (back_tracking2(g, whites, n+1))
            {
                return true;
            }
            else 
            {
                g.at(tmp.x).at(tmp.y) = -2; // back_tracking here 
                light_off_line(g,whites);                
                return back_tracking2(g, whites, n + 1);
            }
        }
    }
    return back_tracking2(g, whites, n+1);
}


void white_init(vector<vector<int> > g,vector<struct point> &whites)
{
    struct point tmp;
    for (int i=0; i<g.size(); i++)
    {
        for (int j=0; j<g[i].size(); j++)
        {
            if (g.at(i).at(j) == -2)
            {
                tmp.x = i;
                tmp.y = j;
                whites.push_back(tmp);
            }
        }
    }
}

bool light_all(vector<vector<int> > g)
{
    light_init(g);

    vector<struct point> whites;
    white_init(g,whites);

    return back_tracking2(g, whites, 0);
}

typedef struct Data{
    vector<vector<int> > g;
    vector<struct point> blacks;
    int n;
    int depth;
    bool re;
    int flag;
}Data;

bool startPthread(vector<vector<int> > g, vector<struct point> blacks, int depth, int flag);

void * back_tracking0(void * d)
{
    Data *data = (Data *)d;
    vector<vector<int> > g = data->g;
    int n = data->n;
    int depth = data->depth;
    vector<struct point> blacks(data->blacks);
    if (depth == blacks.size())
    {
        cout << "error";
        data->re = false;
        return NULL;
    }
    struct point tmp = blacks[depth];
    int x = tmp.x;
    int y = tmp.y;
    int flag = data->flag;
    int total = 0;
    switch (tmp.val)
    {
        case 4:
            if (light_up(g, x-1, y, flag) && light_up(g, x+1, y, flag) &&
                light_up(g, x, y-1, flag) && light_up(g, x, y+1, flag))
            {
                data->re = startPthread(g, blacks, depth+1, flag+1);
                return NULL;
            }
            data->re = false;
            return NULL;
            break;
        case 3:
            switch(n)
            {
                case 0:
                    if (light_up(g, x, y-1, flag) && light_up(g, x, y+1, flag) && light_up(g, x+1, y, flag))
                    {
                        data->re = startPthread(g, blacks, depth+1, flag+1);
                        return NULL;
                    }
                    break;
                case 1:
                    if (light_up(g, x+1, y, flag) && light_up(g, x, y+1, flag) && light_up(g, x-1, y, flag))
                    {
                        data->re = startPthread(g, blacks, depth+1, flag+1);
                    }
                    break;
                case 2:
                    if (light_up(g, x, y+1, flag) && light_up(g, x-1, y, flag) && light_up(g, x, y-1, flag))
                    {
                        data->re = startPthread(g, blacks, depth+1, flag+1);
                    }
                    break;
                case 3:
                    if (light_up(g, x-1, y, flag) && light_up(g, x, y-1, flag) && light_up(g, x+1, y, flag))
                    {
                        data->re = startPthread(g, blacks, depth+1, flag+1);
                    }
                    break;
            }
            data->re = false;
            return NULL;
            break;
        case 2:
            switch(n)
            {
                case 0:
                    if (light_up(g, x-1, y, flag) && light_up(g, x, y-1, flag))
                    {
                        data->re = startPthread(g, blacks, depth+1, flag+1);
                        if (data->re)
                            return NULL;
                    }
                    break;
                case 1:
                    
                    if (light_up(g, x-1, y, flag) && light_up(g, x+1, y, flag))
                    {
                        data->re = startPthread(g, blacks, depth+1, flag+1);
                        if (data->re)
                            return NULL;
                    }
                    break;
                case 2:
                    
                    if (light_up(g, x-1, y, flag) && light_up(g, x, y+1, flag))
                    {
                        data->re = startPthread(g, blacks, depth+1, flag+1);
                        if (data->re)
                            return NULL;
                    }
                    break;
                case 3:
                    
                    if (light_up(g, x, y-1, flag) && light_up(g, x+1, y, flag))
                    {
                        data->re = startPthread(g, blacks, depth+1, flag+1);
                        if (data->re)
                            return NULL;
                    }
                    break;
                case 4:
                    
                    if (light_up(g, x, y-1, flag) && light_up(g, x, y+1, flag))
                    {
                        data->re = startPthread(g, blacks, depth+1, flag+1);
                        if (data->re)
                            return NULL;
                    }
                    break;
                case 5:
                    
                    if (light_up(g, x+1, y, flag) && light_up(g, x, y+1, flag))
                    {
                        data->re = startPthread(g, blacks, depth+1, flag+1);
                        if (data->re)
                            return NULL;
                    }
                    break;
            }
            data->re = false;
            return NULL;
            break;
        case 1:
            switch(n)
            {
                case 0:
                    
                    if (light_up(g, x-1, y, flag))
                    {
                        // g.at(x-1).at(y) = flag;
                        data->re = startPthread(g, blacks, depth+1, flag+1);
                        if (data->re)
                            return NULL;
                    }
                    break;
                case 1:
                    
                    if (light_up(g, x+1, y, flag))
                    {
                        // g.at(x+1).at(y) = flag;
                        data->re = startPthread(g, blacks, depth+1, flag+1);
                        if (data->re)
                            return NULL;
                    }
                    break;
                case 2:
                    
                    if (light_up(g, x, y-1, flag))
                    {
                        // g.at(x).at(y-1) = flag;
                        data->re = startPthread(g, blacks, depth+1, flag+1);
                        if (data->re)
                            return NULL;
                    }
                    break;
                case 3:
                    
                    if (light_up(g, x, y+1, flag))
                    {
                        // g.at(x).at(y+1) = flag;
                        data->re = startPthread(g, blacks, depth+1, flag+1);
                        if (data->re)
                            return NULL;
                    }
                    break;
            }
            data->re = false;
            return NULL;
            break;
    }
    return NULL;
}


bool startPthread(vector<vector<int> > g, vector<struct point> blacks, int depth, int flag)
{
    pthread_t* thread_list;
    Data* data;
    if (depth == blacks.size()) // finial state
    {
        return light_all(g); //solve single thread
    }
    
    struct point black_now = blacks[depth];

    
    int n = g.at(black_now.x).at(black_now.y);
    int thread_num = 0;

    switch(n)
    {
        //case_number
        case 4:
            thread_num = 1;
            break;
        case 3:
            thread_num = 4;
            break;
        case 2:
            thread_num = 6;
            break;
        case 1:
            thread_num = 4;
            break;
    }

    thread_list = (pthread_t *)malloc(sizeof(pthread_t)*thread_num);
    data = (Data*)malloc(sizeof(Data)*thread_num);
    
    //init thread
    memset(data, 0, sizeof(Data)*thread_num);
    for (int i=0; i<thread_num; i++)
    {
        for (int j=0; j<g.size(); j++)
        {
            vector <int> tmp_int;
            for (int k=0; k<g.at(j).size(); k++)
            {
                tmp_int.push_back(g.at(j).at(k));
            }
            data[i].g.push_back(tmp_int);
        }

        data[i].blacks.resize(blacks.size());
        for (int j=0; j<blacks.size(); j++)
        {
            data[i].blacks[j] = blacks[j];
        }
        data[i].n = i;
        data[i].re = false;
        data[i].depth = depth;
        data[i].flag = flag;


        int ret = pthread_create(&thread_list[i], NULL, back_tracking0, (void *)&data[i]);
        if (ret != 0)
        {
            printf("error");
        }
    }


    for (int i=0; i<thread_num; i++)
    {
        pthread_join(thread_list[i], NULL);
    }

    for (int i=0; i<thread_num; i++)
    {
        if (data[i].re)
        {
               free(thread_list);
               free(data);
            return true;
        }
    }
    free(thread_list);
    free(data);
    return false;
}



bool back_tracking(vector<vector<int> > g, vector<struct point> blacks)
{
    return startPthread(g, blacks, 0, 5);
}



vector<vector<int> > solveAkari(vector<vector<int> > & g)
{
    struct point b;
    vector <struct point> blacks;
    for (int i=0; i<g.size(); i++)
    {
        int z = g.at(i).size();
        for (int j=0; j<g.at(i).size(); j++)
        {
            if (g[i][j]>0 && g[i][j]<=4)
            {
                b.x = i;
                b.y = j;
                b.val = g[i][j];
                blacks.push_back(b);
            }
        }
    }
    sort(blacks.begin(), blacks.end(), cmp);

    back_tracking(g, blacks);
    //recover light to white
    for (int i=0; i<result.size(); i++)
    {
        for (int j=0; j<result.at(i).size(); j++)
        {
            if (result.at(i).at(j) == -3)
                result.at(i).at(j) = -2;
            else if (result.at(i).at(j) >= 5)
                result.at(i).at(j) = 5;
        }
    }
    return result;
}

}