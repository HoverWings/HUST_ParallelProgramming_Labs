#include <bits/stdc++.h>
#include "akari.h"
using namespace std;
namespace aka
{
struct Block
{
    int x, y;
    int value;
//    int flag;   //标志点灯的递归层数，下层递归回溯时不能熄灭上层递归点亮的灯
};
vector<struct Block> blacks;

bool sortFunc(const struct Block &b1, const struct Block &b2)
{
    return b1.value > b2.value;
}

void print_g(vector<vector<int> > & g)
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

//判断(x,y)附近能否再放一个灯泡
bool can_add_light(vector<vector<int> > & g, int x, int y)
{
    if (x < 0 || y < 0 || x>=g.size() || y>=g.at(0).size())//墙旁边可以放
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

//判断(x,y)能否放一个灯泡，可以则放置
bool light_up(vector<vector<int> > & g, int x, int y, int flag)
{
    if (x < 0 || y < 0 || x>=g.size() || y>=g.at(0).size())
        return false;
    else if (g.at(x).at(y) >= 5) //已经有灯泡
        return true;
    else if (g.at(x).at(y) > -2)   //是墙
        return false;
    else
    {
        //判断灯泡的上下左右格子能否容纳新增加的灯泡
        if (can_add_light(g, x, y+1) && can_add_light(g, x, y-1)
                && can_add_light(g, x-1, y) && can_add_light(g, x+1, y))
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

//拿掉flag层递归放置的灯，非flag层的保留
void light_down(vector<vector<int> > &g, int x, int y, int flag)
{
    if (x < 0 || y < 0 || x>=g.size() || y>=g.at(0).size())
        return;
    if (g.at(x).at(y) >= 5)
    {
        if (g.at(x).at(y) == flag)
        //关灯不能影响周围已经布置好灯的黑色格子，即上层递归放置的灯
            g.at(x).at(y) = -2;
        return;
    }
    return;
}

//将(x, y)处灯可照亮的方块值设为-3，返回新照亮的块(未实现)
void light_xy(vector<vector<int> > &g, int x, int y)
{
    struct Block tmp;
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

bool is_ok(vector<vector<int> > &g, vector<struct Block> whites)
{
    for (int i=0; i<whites.size(); i++)
    {
        if (g.at(whites[i].x).at(whites[i].y) == -2)
            return false;
    }
    return true;
}

//回溯法在还未照亮的方块放灯泡
bool back_tracking2(vector<vector<int> > &g, vector<struct Block> whites, int n)
{
    if (n == whites.size())
    {
        if (is_ok(g, whites))
            return true;
        else
            return false;
    }
    struct Block tmp;
    tmp = whites[n];
    int value = g.at(tmp.x).at(tmp.y);
    if (value <= -2)
    {
        if (light_up(g, tmp.x, tmp.y, 5))
        {
            light_xy(g, tmp.x, tmp.y);
            {
                if (back_tracking2(g, whites, n+1))
                {
                    return true;
                }
                else
                {
                    light_down(g, tmp.x, tmp.y, 5);
                    for (int i=0; i<whites.size(); i++)
                    {
                        if (g.at(whites[i].x).at(whites[i].y) == -3)
                            g.at(whites[i].x).at(whites[i].y) = -2;
                    }
                    for (int i=0; i<whites.size(); i++)
                    {
                        if (g.at(whites[i].x).at(whites[i].y) >= 5)
                            light_xy(g, whites[i].x, whites[i].y);
                    }
                    return back_tracking2(g, whites, n+1);
                }
            }
        }
    }
    return back_tracking2(g, whites, n+1);
}

//在还未照亮的方块放灯泡
bool light_all(vector<vector<int> > &g)
{
    //点亮所有当前照亮的方块
    for (int i=0; i<g.size(); i++)
    {
        for (int j=0; j<g[i].size(); j++)
        {
            if (g.at(i).at(j) >= 5)
            {
                light_xy(g, i, j);
            }
        }
    }
    //找到当前未照亮的方块
    vector<struct Block> whites;
    struct Block tmp;
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
    //print_g(g);
    back_tracking2(g, whites, 0);
    //print_g(g);
    for (int i=0; i<whites.size(); i++)
    {
        if (g.at(whites[i].x).at(whites[i].y) == -2)
            //还有块未照亮
            return false;
    }
    //back_tracking2中使用-3标志被照亮的方块，5以上数字标识电灯泡以及放置此灯泡的递归层数
    for (int i=0; i<g.size(); i++)
    {
        for (int j=0; j<g.at(i).size(); j++)
        {
            if (g.at(i).at(j) == -3)
                g.at(i).at(j) = -2;
            else if (g.at(i).at(j) >= 5)
                g.at(i).at(j) = 5;
        }
    }
    return true;
}

//判断(x, y)处是否是数值为1-4的黑色方块
bool is_black14(vector<vector<int> > &g, int x, int y)
{
    if (x<0 || x>=g.size() || y<0 || y>=g[0].size())
    {   //x、y不在合法范围
        return false;
    }
    if (g.at(x).at(y)>=1 && g.at(x).at(y)<=4)
        return true;
    return false;
}

//清除所有不靠1-4的黑色方块的灯及所有灯照亮的地方
void clear_light(vector<vector<int> > &g)
{
    for (int i=0; i<g.size(); i++)
    {
        for (int j=0; j<g.at(i).size(); j++)
        {
            if (g.at(i).at(j) == -3)
                g.at(i).at(j) = -2;
            else if (g.at(i).at(j) >= 5 && !is_black14(g, i-1, j)
                     && !is_black14(g, i+1, j) && !is_black14(g, i, j-1) && !is_black14(g, i, j+1)) //是不靠1-4的黑色方块的灯
                g.at(i).at(j) = -2;
        }
    }
}


bool back_tracking1(vector<vector<int> > &g, vector<struct Block> blacks, int n)
{
//   for (int i=n; i<blacks.size(); i++)
//   {
    static int flag = 5;
    int i=n;
    if (n == blacks.size())
    {
        static int i = 0;
//        printf("\nt:%d", i++);
//        print_g(g);
        if (!light_all(g))
        {
            clear_light(g);
            //printf("debug\n");
            return false;
        }
        return true;
    }
    struct Block tmp = blacks[i];
    int x = tmp.x, y = tmp.y;

    switch (tmp.value)
    {
    case 4:
        flag++;
        if (light_up(g, x-1, y, flag) && light_up(g, x+1, y, flag) &&
                light_up(g, x, y-1, flag) && light_up(g, x, y+1, flag))
        {
            return back_tracking1(g, blacks, i+1);
        }
        light_down(g, x-1, y, flag);
        light_down(g, x+1, y, flag);
        light_down(g, x, y-1, flag);
        light_down(g, x, y+1, flag);
        flag--;
        return false;
        break;
    case 3:
        //左右下
        flag++;
        if (light_up(g, x, y-1, flag) && light_up(g, x, y+1, flag) && light_up(g, x+1, y, flag))
        {
            if (back_tracking1(g, blacks, i+1))
                return true;
        }

        light_down(g, x, y-1, flag);
        light_down(g, x, y+1, flag);
        light_down(g, x+1, y, flag);
        //下右上
        if (light_up(g, x+1, y, flag) && light_up(g, x, y+1, flag) && light_up(g, x-1, y, flag))
        {
            if(back_tracking1(g, blacks, i+1))
                return true;
        }
        light_down(g, x+1, y, flag);
        light_down(g, x, y+1, flag);
        light_down(g, x-1, y, flag);
        //右上左
        if (light_up(g, x, y+1, flag) && light_up(g, x-1, y, flag) && light_up(g, x, y-1, flag))
        {
            if(back_tracking1(g, blacks, i+1))
                return true;
        }
        light_down(g, x, y+1, flag);
        light_down(g, x-1, y, flag);
        light_down(g, x, y-1, flag);
        //上左下
        if (light_up(g, x-1, y, flag) && light_up(g, x, y-1, flag) && light_up(g, x+1, y, flag))
        {
            if(back_tracking1(g, blacks, i+1))
                return true;
        }
        light_down(g, x-1, y, flag);
        light_down(g, x, y-1, flag);
        light_down(g, x+1, y, flag);
        flag--;
        return false;
        break;
    case 2:
        //上左
        flag++;
        if (light_up(g, x-1, y, flag) && light_up(g, x, y-1, flag))
        {
            if (back_tracking1(g, blacks, i+1))
                return true;
        }
        light_down(g, x-1, y, flag);
        light_down(g, x, y-1, flag);
        //上下
        if (light_up(g, x-1, y, flag) && light_up(g, x+1, y, flag))
        {
            if(back_tracking1(g, blacks, i+1))
                return true;
        }
        light_down(g, x-1, y, flag);
        light_down(g, x+1, y, flag);
        //上右
        if (light_up(g, x-1, y, flag) && light_up(g, x, y+1, flag))
        {
            if(back_tracking1(g, blacks, i+1))
                return true;
        }
        light_down(g, x-1, y, flag);
        light_down(g, x, y+1, flag);
        //左下
        if (light_up(g, x, y-1, flag) && light_up(g, x+1, y, flag))
        {
            if(back_tracking1(g, blacks, i+1))
                return true;
        }
        light_down(g, x, y-1, flag);
        light_down(g, x+1, y, flag);
        //左右
        if (light_up(g, x, y-1, flag) && light_up(g, x, y+1, flag))
        {
            if(back_tracking1(g, blacks, i+1))
                return true;
        }
        light_down(g, x, y-1, flag);
        light_down(g, x, y+1, flag);
        //下右
        if (light_up(g, x+1, y, flag) && light_up(g, x, y+1, flag))
        {
            if(back_tracking1(g, blacks, i+1))
                return true;
        }
        light_down(g, x+1, y, flag);
        light_down(g, x, y+1, flag);
        flag--;
        return false;
        break;
    case 1:
        //上
        flag++;
        if (light_up(g, x-1, y, flag))
        {
            if (back_tracking1(g, blacks, i+1))
                return true;
        }
        light_down(g, x-1, y, flag);
        //下
        if (light_up(g, x+1, y, flag))
        {
            if(back_tracking1(g, blacks, i+1))
                return true;
        }
        light_down(g, x+1, y, flag);
        //左
        if (light_up(g, x, y-1, flag))
        {
            if(back_tracking1(g, blacks, i+1))
                return true;
        }
        light_down(g, x, y-1, flag);
        //右
        if (light_up(g, x, y+1, flag))
        {
            if(back_tracking1(g, blacks, i+1))
                return true;
        }
        light_down(g, x, y+1, flag);
        flag--;
        return false;
        break;
    }
    return false;
//    }
}

vector<vector<int> > solveAkari(vector<vector<int> > & g)
{
    // 请在此函数内返回最后求得的结果
    struct Block b;
    for (int i=0; i<g.size(); i++)
    {
        int z = g.at(i).size();
        for (int j=0; j<g.at(i).size(); j++)
        {

            if (g[i][j]>0 && g[i][j]<=4)
            {
                b.x = i;
                b.y = j;
                b.value = g[i][j];
                blacks.push_back(b);
            }
        }
    }
    sort(blacks.begin(), blacks.end(), sortFunc);
    //在所有黑色方块边放灯泡
    if (!back_tracking1(g, blacks, 0))
        printf("--not find--\n");
    //点亮所有未照亮的方块

    return g;
}



}
