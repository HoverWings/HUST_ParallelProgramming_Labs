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
//    int flag;   //��־��Ƶĵݹ�������²�ݹ����ʱ����Ϩ���ϲ�ݹ�����ĵ�
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

//�ж�(x,y)�����ܷ��ٷ�һ������
    bool can_add_light(vector<vector<int> > g, int x, int y)
    {
        if (x < 0 || y < 0 || x>=g.size() || y>=g.at(0).size())//ǽ�Ա߿��Է�
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

//�ж�(x,y)�ܷ��һ�����ݣ����������
    bool light_up(vector<vector<int> > g, int x, int y, int flag)
    {
        if (x < 0 || y < 0 || x>=g.size() || y>=g.at(0).size())
            return false;
        else if (g.at(x).at(y) >= 5) //�Ѿ��е���
            return true;
        else if (g.at(x).at(y) > -2)   //��ǽ
            return false;
        else
        {
            //�жϵ��ݵ��������Ҹ����ܷ����������ӵĵ���
            if (can_add_light(g, x, y+1) && can_add_light(g, x, y-1)
                && can_add_light(g, x-1, y) && can_add_light(g, x+1, y))
            {
                //�ж��Ƿ��е��ݻ�������
                //��
                for (int i=x-1; i>=0; i--)
                    if (g.at(i).at(y)>=-1 && g.at(i).at(y)<=4)//����ǽ
                        break;
                    else if (g.at(i).at(y) >= 5)
                        return false;
                //��
                for (int i=x+1; i<g.size(); i++)
                    if (g.at(i).at(y)>=-1 && g.at(i).at(y)<=4)//����ǽ
                        break;
                    else if (g.at(i).at(y) >= 5)
                        return false;
                //��
                for (int i=y-1; i>=0; i--)
                    if (g.at(x).at(i)>=-1 && g.at(x).at(i)<=4)//����ǽ
                        break;
                    else if (g.at(x).at(i) >= 5)
                        return false;
                //��
                for (int i=y+1; i<g.at(x).size(); i++)
                    if (g.at(x).at(i)>=-1 && g.at(x).at(i)<=4)//����ǽ
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


    bool is_ok(vector<vector<int> > g, vector<struct Block> whites) {
        for (int i = 0; i < whites.size(); i++) {
            if (g.at(whites[i].x).at(whites[i].y) == -2)
                return false;
        }
        return true;
    }

//���ݷ��ڻ�δ�����ķ���ŵ���
    bool back_tracking2(vector<vector<int> > g, vector<struct Block> whites, int n)
    {
//        cout << "9\n";
        if (n == whites.size())
        {
            if (is_ok(g, whites))
            {
                if (get_result)
                    return true;
                result.resize(g.size());
                for (int i=0; i<g.size(); i++)
                {
                    result[i].resize(g[i].size());
                    for (int j=0; j<g[i].size(); j++)
                    {
                        result.at(i).at(j) = g.at(i).at(j);
                    }
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
            if (light_up(g, tmp.x, tmp.y, 5))
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

//�ڻ�δ�����ķ���ŵ���
    bool light_all(vector<vector<int> > g)
    {
//        cout << "light_all\n";
        //�������е�ǰ�����ķ���
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
        //�ҵ���ǰδ�����ķ���
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

    bool startPthread(vector<vector<int> > g, vector<struct Block> blacks, int depth, int flag);

    void * back_tracking0(void * d)
    {
//        cout << "6\n";
        struct Data *data = (struct Data *)d;
        vector<vector<int> > g = data->g;
        int n = data->n;
        int depth = data->depth;
        vector<struct Block> blacks(data->blacks);
//        blacks.assign(data->blacks.begin(), data->blacks.end());
        if (depth == blacks.size())
        {
            cout << "error";
            data->re = false;
            return NULL;
        }
//        cout << "7\n";
        struct Block tmp = blacks[depth];
        int x = tmp.x, y = tmp.y;
        int flag = data->flag;

        //cout << "x:" << x << "  y:" << y << "  value:" << tmp.value << "  n:" << n << endl;
        //std::cout << "value:" << tmp.value << "  �߳�" << n << endl;
        switch (tmp.value)
        {
            case 4:
                if (light_up(g, x-1, y, flag) && light_up(g, x+1, y, flag) &&
                    light_up(g, x, y-1, flag) && light_up(g, x, y+1, flag))
                {
                    //������һ�����
                    g.at(x-1).at(y) = flag;
                    g.at(x+1).at(y) = flag;
                    g.at(x).at(y-1) = flag;
                    g.at(x).at(y+1) = flag;
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
                        //������
                        if (light_up(g, x, y-1, flag) && light_up(g, x, y+1, flag) && light_up(g, x+1, y, flag))
                        {
                            g.at(x).at(y-1) = flag;
                            g.at(x).at(y+1) = flag;
                            g.at(x+1).at(y) = flag;
                            data->re = startPthread(g, blacks, depth+1, flag+1);
                            return NULL;
                        }
                        if (can_add_light(g, x, y-1))
                        break;
                    case 1:
                        //������
                        if (light_up(g, x+1, y, flag) && light_up(g, x, y+1, flag) && light_up(g, x-1, y, flag))
                        {
                            g.at(x+1).at(y) = flag;
                            g.at(x).at(y+1) = flag;
                            g.at(x-1).at(y) = flag;
                            data->re = startPthread(g, blacks, depth+1, flag+1);
                            if (data->re)
                                return NULL;
                        }
                        break;
                    case 2:
                        //������
                        if (light_up(g, x, y+1, flag) && light_up(g, x-1, y, flag) && light_up(g, x, y-1, flag))
                        {
                            g.at(x).at(y+1) = flag;
                            g.at(x-1).at(y) = flag;
                            g.at(x).at(y-1) = flag;
                            data->re = startPthread(g, blacks, depth+1, flag+1);
                            if (data->re)
                                return NULL;
                        }
                        break;
                    case 3:
                        //������
                        if (light_up(g, x-1, y, flag) && light_up(g, x, y-1, flag) && light_up(g, x+1, y, flag))
                        {
                            g.at(x-1).at(y) = flag;
                            g.at(x).at(y-1) = flag;
                            g.at(x+1).at(y) = flag;
                            data->re = startPthread(g, blacks, depth+1, flag+1);
                            if (data->re)
                                return NULL;
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
                        //����
                        if (light_up(g, x-1, y, flag) && light_up(g, x, y-1, flag))
                        {
                            g.at(x-1).at(y) = flag;
                            g.at(x).at(y-1) = flag;
                            data->re = startPthread(g, blacks, depth+1, flag+1);
                            if (data->re)
                                return NULL;
                        }
                        break;
                    case 1:
                        //����
                        if (light_up(g, x-1, y, flag) && light_up(g, x+1, y, flag))
                        {
                            g.at(x-1).at(y) = flag;
                            g.at(x+1).at(y) = flag;
                            data->re = startPthread(g, blacks, depth+1, flag+1);
                            if (data->re)
                                return NULL;
                        }
                        break;
                    case 2:
                        //����
                        if (light_up(g, x-1, y, flag) && light_up(g, x, y+1, flag))
                        {
                            g.at(x-1).at(y) = flag;
                            g.at(x).at(y+1) = flag;
                            data->re = startPthread(g, blacks, depth+1, flag+1);
                            if (data->re)
                                return NULL;
                        }
                        break;
                    case 3:
                        //����
                        if (light_up(g, x, y-1, flag) && light_up(g, x+1, y, flag))
                        {
                            g.at(x).at(y-1) = flag;
                            g.at(x+1).at(y) = flag;
                            data->re = startPthread(g, blacks, depth+1, flag+1);
                            if (data->re)
                                return NULL;
                        }
                        break;
                    case 4:
                        //����
                        if (light_up(g, x, y-1, flag) && light_up(g, x, y+1, flag))
                        {
                            g.at(x).at(y-1) = flag;
                            g.at(x).at(y+1) = flag;
                            data->re = startPthread(g, blacks, depth+1, flag+1);
                            if (data->re)
                                return NULL;
                        }
                        break;
                    case 5:
                        //����
                        if (light_up(g, x+1, y, flag) && light_up(g, x, y+1, flag))
                        {
                            g.at(x+1).at(y) = flag;
                            g.at(x).at(y+1) = flag;
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
                        //��
                        if (light_up(g, x-1, y, flag))
                        {
                            g.at(x-1).at(y) = flag;
                            data->re = startPthread(g, blacks, depth+1, flag+1);
                            if (data->re)
                                return NULL;
                        }
                        break;
                    case 1:
                        //��
                        if (light_up(g, x+1, y, flag))
                        {
                            g.at(x+1).at(y) = flag;
                            data->re = startPthread(g, blacks, depth+1, flag+1);
                            if (data->re)
                                return NULL;
                        }
                        break;
                    case 2:
                        //��
                        if (light_up(g, x, y-1, flag))
                        {
                            g.at(x).at(y-1) = flag;
                            data->re = startPthread(g, blacks, depth+1, flag+1);
                            if (data->re)
                                return NULL;
                        }
                        break;
                    case 3:
                        //��
                        if (light_up(g, x, y+1, flag))
                        {
                            g.at(x).at(y+1) = flag;
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


    bool startPthread(vector<vector<int> > g, vector<struct Block> blacks, int depth, int flag)
    {
//        cout << "1\n";
        pthread_t* th_list;
        struct Data* data;
        if (depth == blacks.size())
        {
//            cout << "lightall\n";
//            cout << "2";
            return light_all(g);
        }
        //������һ����ɫ�������ֵ�����߳�
//        cout << "2\n";
        struct Block tmp1 = blacks[depth];
//        cout << "3\n";
        int n = g.at(tmp1.x).at(tmp1.y);
        int th_num = 0;
        switch(n)
        {
            case 4:
                th_num = 1;
                break;
            case 3:
                th_num = 4;
                break;
            case 2:
                th_num = 6;
                break;
            case 1:
                th_num = 4;
                break;
        }
        th_list = (pthread_t *)malloc(sizeof(pthread_t)*th_num);
        data = (struct Data*)malloc(sizeof(struct Data)*th_num);
        memset(data, 0, sizeof(struct Data)*th_num);
//        cout << "4\n";
        for (int i=0; i<th_num; i++)
        {
            //printf("--%d", i);
//            cout << "5\n";
//            data[i].g.reserve(g.size());
//            data[i].g.resize(g.size());
            for (int j=0; j<g.size(); j++)
            {
//                cout << "5.1\n";
//                data[i].g[j].reserve(g[j].size());
//                data[i].g[j].resize(g[j].size());
                vector <int> tmp_int;
                for (int k=0; k<g.at(j).size(); k++)
                {
//                    cout << "5.2\n";
//                    data[i].g.at(j).at(k) = g.at(j).at(k);
                    tmp_int.push_back(g.at(j).at(k));
                }
                data[i].g.push_back(tmp_int);
            }
//            cout << "6\n";
            data[i].blacks.resize(blacks.size());
            for (int j=0; j<blacks.size(); j++)
            {
                data[i].blacks[j] = blacks[j];
            }
            data[i].n = i;
            data[i].re = false;
            data[i].depth = depth;
            data[i].flag = flag;
//            cout << "7\n";
            int ret = pthread_create(&th_list[i], NULL, back_tracking0, (void *)&data[i]);
//            cout << "8\n";
            if (ret != 0)
            {
                printf("error");
            }
        }
//        cout << "9\n";
        for (int i=0; i<th_num; i++)
        {
            pthread_join(th_list[i], NULL);
        }
        for (int i=0; i<th_num; i++)
        {
            if (data[i].re)
            {
//                for (int j=0; j<g.size(); j++)
//                {
////                    tdata[i].g[j].resize(g[j].size());
//                    for (int k=0; k<g[j].size(); k++)
//                    {
//                        g.at(j).at(k) = tdata[i].g.at(j).at(k);
//                    }
//                }
//                free(th_list);
//                free(data);
//                cout << "2\n";
                return true;
            }
        }
//        free(th_list);
//        free(data);
//        cout << "2\n";
        return false;
    }



    bool back_tracking(vector<vector<int> > g, vector<struct Block> blacks)
    {
//        cout << "back_tracking\n";
        return startPthread(g, blacks, 0, 5);

    }



    vector<vector<int> > solveAkari(vector<vector<int> > & g)
    {
        // ���ڴ˺����ڷ��������õĽ��
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
        //�����к�ɫ����߷ŵ���
//        if (!back_tracking(g, blacks))
        back_tracking(g, blacks);
//            printf("--not find--\n");
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
        //��������δ�����ķ���

        return result;
    }



}