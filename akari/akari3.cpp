#include <bits/stdc++.h>
#include "akari.h"
using namespace std;
vector<vector<int> > result;
int get_result = 0;
namespace aka
{
    struct Block
    {
        int x, y;
        int value;
//    int flag;   
    };
//    vector<struct Block> blacks;

    bool sortFunc(const struct Block &b1, const struct Block &b2)
    {
        return b1.value > b2.value;
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

//ж(x,y)ܷٷһ
    bool can_add_light(vector<vector<int> > g, int x, int y)
    {
        if (x < 0 || y < 0 || x>=g.size() || y>=g.at(0).size())//ǽԱ߿Է
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

//ж(x,y)ܷһݣ
    bool light_up(vector<vector<int> > g, int x, int y)
    {
        if (x < 0 || y < 0 || x>=g.size() || y>=g.at(0).size())
            return false;
        else if (g.at(x).at(y) >= 5) //Ѿе
            return true;
        else if (g.at(x).at(y) > -2)   //ǽ
            return false;
        else
        {
            //жϵݵҸܷӵĵ
            if (can_add_light(g, x, y+1) && can_add_light(g, x, y-1)
                && can_add_light(g, x-1, y) && can_add_light(g, x+1, y))
            {
                //жǷеݻ
                //
                for (int i=x-1; i>=0; i--)
                    if (g.at(i).at(y)>=-1 && g.at(i).at(y)<=4)//ǽ
                        break;
                    else if (g.at(i).at(y) >= 5)
                        return false;
                //
                for (int i=x+1; i<g.size(); i++)
                    if (g.at(i).at(y)>=-1 && g.at(i).at(y)<=4)//ǽ
                        break;
                    else if (g.at(i).at(y) >= 5)
                        return false;
                //
                for (int i=y-1; i>=0; i--)
                    if (g.at(x).at(i)>=-1 && g.at(x).at(i)<=4)//ǽ
                        break;
                    else if (g.at(x).at(i) >= 5)
                        return false;
                //
                for (int i=y+1; i<g.at(x).size(); i++)
                    if (g.at(x).at(i)>=-1 && g.at(x).at(i)<=4)//ǽ
                        break;
                    else if (g.at(x).at(i) >= 5)
                        return false;
                g.at(x).at(y) = 5;

                return true;
            }
            return false;
        }
        return false;
    }


    bool is_ok(vector<vector<int> > g, vector<struct Block> whites) {
        for (int i = 0; i < whites.size(); i++) {
            if (g.at(whites[i].x).at(whites[i].y) == -2)
                return false;
        }
        return true;
    }

//ݷڻδķŵ
    bool back_tracking2(vector<vector<int> > g, vector<struct Block> whites, int n)
    {
//        cout << "9\n";
        if (n == whites.size())
        {
            if (is_ok(g, whites))
            {
//                cout << "find\n";
                if (get_result)
                    return true;
                for (int j=0; j<g.size(); j++)
                {
                    vector <int> tmp_int;
                    for (int k=0; k<g.at(j).size(); k++)
                    {
//                    cout << "5.2\n";
//                    data[i].g.at(j).at(k) = g.at(j).at(k);
                        tmp_int.push_back(g.at(j).at(k));
                    }
                    result.push_back(tmp_int);
                }
                get_result = 1;
                return true;
            }
            else
                return false;
        }
        struct Block tmp;
        tmp = whites[n];
//        cout << "10\n";
        int value = g.at(tmp.x).at(tmp.y);
        if (value == -2)
        {
            if (light_up(g, tmp.x, tmp.y))
            {
                g.at(tmp.x).at(tmp.y) = 5;
                for (int k=tmp.x+1; k<g.size(); k++)
                {
                    if (g.at(k).at(tmp.y)>=-1 &&  g.at(k).at(tmp.y)<=4)
                        break;
                    else
                        g.at(k).at(tmp.y) = -3;
                }
                for (int k=tmp.x-1; k>=0; k--)
                {
                    if (g.at(k).at(tmp.y)>=-1 &&  g.at(k).at(tmp.y)<=4)
                        break;
                    else
                        g.at(k).at(tmp.y) = -3;
                }
                for (int k=tmp.y+1; k<g.at(tmp.x).size(); k++)
                {
                    if (g.at(tmp.x).at(k)>=-1 &&  g.at(tmp.x).at(k)<=4)
                        break;
                    else
                        g.at(tmp.x).at(k) = -3;
                }
                for (int k=tmp.y-1; k>=0; k--)
                {
                    if (g.at(tmp.x).at(k)>=-1 &&  g.at(tmp.x).at(k)<=4)
                        break;
                    else
                        g.at(tmp.x).at(k) = -3;
                }
                if (back_tracking2(g, whites, n+1))
                {
                    return true;
                }
                else {
                    g.at(tmp.x).at(tmp.y) = -2;
                    for (int i = 0; i < whites.size(); i++) {
                        if (g.at(whites[i].x).at(whites[i].y) == -3)
                            g.at(whites[i].x).at(whites[i].y) = -2;
                    }
                    for (int i = 0; i < whites.size(); i++) {
                        if (g.at(whites[i].x).at(whites[i].y) >= 5)
                        {
                            struct Block tmp = whites[i];
                            for (int k=tmp.x+1; k<g.size(); k++)
                            {
                                if (g.at(k).at(tmp.y)>=-1 &&  g.at(k).at(tmp.y)<=4)
                                    break;
                                else
                                    g.at(k).at(tmp.y) = -3;
                            }
                            for (int k=tmp.x-1; k>=0; k--)
                            {
                                if (g.at(k).at(tmp.y)>=-1 &&  g.at(k).at(tmp.y)<=4)
                                    break;
                                else
                                    g.at(k).at(tmp.y) = -3;
                            }
                            for (int k=tmp.y+1; k<g.at(tmp.x).size(); k++)
                            {
                                if (g.at(tmp.x).at(k)>=-1 &&  g.at(tmp.x).at(k)<=4)
                                    break;
                                else
                                    g.at(tmp.x).at(k) = -3;
                            }
                            for (int k=tmp.y-1; k>=0; k--)
                            {
                                if (g.at(tmp.x).at(k)>=-1 &&  g.at(tmp.x).at(k)<=4)
                                    break;
                                else
                                    g.at(tmp.x).at(k) = -3;
                            }
                        }
                    }
                    return back_tracking2(g, whites, n + 1);
                }
            }
        }
        return back_tracking2(g, whites, n+1);
    }

//ڻδķŵ
    bool light_all(vector<vector<int> > g)
    {
//        cout << "light_all\n";
        //еǰķ
        for (int i=0; i<g.size(); i++)
        {
            for (int j=0; j<g[i].size(); j++)
            {
                if (g.at(i).at(j) >= 5)
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
        //ҵǰδķ
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

        return back_tracking2(g, whites, 0);
    }

    struct Data{
        vector<vector<int> > g;
        vector<struct Block> blacks;
        int n;
        int depth;
        bool re;
        int flag;
    };

    bool back_tracking(vector<vector<int> > g, vector<struct Block> blacks, int depth);

    void * new_thread(void * d)
    {
        struct Data *data = (struct Data *)d;
        vector<vector<int> > g = data->g;
        int n = data->n;
        int depth = data->depth;
        vector<struct Block> blacks(data->blacks);
//        blacks.assign(data->blacks.begin(), data->blacks.end());
        if (depth == blacks.size())
        {
            cout << "error1\n";
            data->re = false;
            return NULL;
        }
        struct Block tmp = blacks[depth];
        int x = tmp.x, y = tmp.y;
        if (tmp.value != 3)
        {
            cout << "error2\n";
            data->re = false;
            return NULL;
        }
        switch(n)
        {
            case 0:
                //
                if (light_up(g, x, y-1) && light_up(g, x, y+1) && light_up(g, x+1, y))
                {
                    g.at(x).at(y-1) = 5;
                    g.at(x).at(y+1) = 5;
                    g.at(x+1).at(y) = 5;
                    data->re = back_tracking(g, blacks, depth+1);
                }
                break;
            case 1:
                //
                if (light_up(g, x+1, y) && light_up(g, x, y+1) && light_up(g, x-1, y))
                {
                    g.at(x+1).at(y) = 5;
                    g.at(x).at(y+1) = 5;
                    g.at(x-1).at(y) = 5;
                    data->re = back_tracking(g, blacks, depth+1);
                }
                break;
            case 2:
                //
                if (light_up(g, x, y+1) && light_up(g, x-1, y) && light_up(g, x, y-1))
                {
                    g.at(x).at(y+1) = 5;
                    g.at(x-1).at(y) = 5;
                    g.at(x).at(y-1) = 5;
                    data->re = back_tracking(g, blacks, depth+1);
                }
                break;
            case 3:
                //
                if (light_up(g, x-1, y) && light_up(g, x, y-1) && light_up(g, x+1, y))
                {
                    g.at(x-1).at(y) = 5;
                    g.at(x).at(y-1) = 5;
                    g.at(x+1).at(y) = 5;
                    data->re = back_tracking(g, blacks, depth+1);
                }
                break;
        }
        return NULL;
    }

    bool back_tracking(vector<vector<int> > g, vector<struct Block> blacks, int depth)
    {
        if (depth == blacks.size())
        {
            return light_all(g);
        }
        struct Block tmp = blacks[depth];
        int x = tmp.x, y = tmp.y;

        if (tmp.value == 4) {
            if (light_up(g, x - 1, y) && light_up(g, x + 1, y) &&
                light_up(g, x, y - 1) && light_up(g, x, y + 1)) {
                g.at(x-1).at(y) = 5;
                g.at(x+1).at(y) = 5;
                g.at(x).at(y-1) = 5;
                g.at(x).at(y+1) = 5;
                return back_tracking(g, blacks, depth + 1);
            }
            //有值为4的方块周围不能全部点亮
            return false;
        }
        else if (tmp.value == 3) {
            //遇到值为3的方块，分裂产生新线程
            int th_num = 4;
            pthread_t* th_list = (pthread_t *)malloc(sizeof(pthread_t)*th_num);
            struct Data* data = (struct Data*)malloc(sizeof(struct Data)*th_num);
            memset(data, 0, sizeof(struct Data)*th_num);
            for (int i=0; i<th_num; i++)
            {
                //拷贝当前g
                for (int j=0; j<g.size(); j++)
                {
                    vector <int> tmp_int;
                    for (int k=0; k<g.at(j).size(); k++)
                    {
                        tmp_int.push_back(g.at(j).at(k));
                    }
                    data[i].g.push_back(tmp_int);
                }
                //拷贝存储黑色方块的vector
                for (int j=0; j<blacks.size(); j++)
                {
                    data[i].blacks.push_back(blacks[j]);
                }
                data[i].n = i;
                data[i].re = false;
                data[i].depth = depth;
//                    data[i].flag = flag;
                int ret = pthread_create(&th_list[i], NULL, new_thread, (void *)&data[i]);
                if (ret != 0)
                {
                    printf("error3\n");
                }
            }
            for (int i=0; i<th_num; i++)
            {
                pthread_join(th_list[i], NULL);
            }
            for (int i=0; i<th_num; i++)
            {
                if (data[i].re)
                {
//                    free(th_list);
//                    free(data);
                    return true;
                }
            }
//            free(th_list);
//            free(data);
            return false;
        }
        else if (tmp.value == 2) {
            //上左

            if (light_up(g, x - 1, y) && light_up(g, x, y - 1)) {
                vector <vector<int> > tg(g);
                tg.at(x-1).at(y) = 5;
                tg.at(x).at(y-1) = 5;
                if (back_tracking(tg, blacks, depth + 1))
                    return true;
            }
            //上下
            if (light_up(g, x - 1, y) && light_up(g, x + 1, y)) {
                vector <vector<int> > tg(g);
                tg.at(x-1).at(y) = 5;
                tg.at(x+1).at(y) = 5;
                if (back_tracking(tg, blacks, depth + 1))
                    return true;
            }
            //上右
            if (light_up(g, x - 1, y) && light_up(g, x, y + 1)) {
                vector <vector<int> > tg(g);
                tg.at(x-1).at(y) = 5;
                tg.at(x).at(y+1) = 5;
                if (back_tracking(tg, blacks, depth + 1))
                    return true;
            }

            //左下
            if (light_up(g, x, y - 1) && light_up(g, x + 1, y)) {
                vector <vector<int> > tg(g);
                tg.at(x).at(y-1) = 5;
                tg.at(x+1).at(y) = 5;
                if (back_tracking(tg, blacks, depth + 1))
                    return true;
            }
            //左右
            if (light_up(g, x, y - 1) && light_up(g, x, y + 1)) {
                vector <vector<int> > tg(g);
                tg.at(x).at(y-1) = 5;
                tg.at(x).at(y+1) = 5;
                if (back_tracking(tg, blacks, depth + 1))
                    return true;
            }
            //下右
            if (light_up(g, x + 1, y) && light_up(g, x, y + 1)) {
                vector <vector<int> > tg(g);
                tg.at(x+1).at(y) = 5;
                tg.at(x).at(y+1) = 5;
                if (back_tracking(tg, blacks, depth + 1))
                    return true;
            }
            return false;
        }
        else if (tmp.value == 1) {
            //上
            if (light_up(g, x-1, y))
            {
                vector <vector<int> > tg(g);
                tg.at(x-1).at(y) = 5;
                if (back_tracking(tg, blacks, depth + 1))
                    return true;
            }
            //下
            if (light_up(g, x+1, y))
            {
                vector <vector<int> > tg(g);
                tg.at(x+1).at(y) = 5;
                if (back_tracking(tg, blacks, depth + 1))
                    return true;
            }
            //左
            if (light_up(g, x, y-1))
            {
                vector <vector<int> > tg(g);
                tg.at(x).at(y-1) = 5;
                if (back_tracking(tg, blacks, depth + 1))
                    return true;
            }
            //右
            if (light_up(g, x, y+1))
            {
                vector <vector<int> > tg(g);
                tg.at(x).at(y+1) = 5;
                if (back_tracking(tg, blacks, depth + 1))
                    return true;
            }
            return false;
        }
        return false;
    }



    vector<vector<int> > solveAkari(vector<vector<int> > & g)
    {
        // ڴ˺ڷõĽ
        struct Block b;
        vector <struct Block> blacks;
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
        //кɫ߷ŵ
        if (!back_tracking(g, blacks, 0))
            printf("--not find--\n");
//        back_tracking(g, blacks, 0);
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
        //δķ

        return result;
    }



}