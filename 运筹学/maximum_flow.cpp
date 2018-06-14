//Ford-Fulkerson算法求最大流
#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <stack>
using namespace std;

#define V 100
void print_Matrix(int(*M)[V], int n){
    //这个函数是调试的时候用的
    cout << "___MATRIX___"<<endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << M[i][j] << "\t";
        }cout << endl;
    }cout << endl;
}

bool bfs(int rGraph[V][V], int s, int t, int pre[])
{//广度优先搜索，检查当前能否从s到t；维护前驱数组pre
    bool visit[V];//访问标记
    memset(visit, 0, sizeof(visit));
    queue <int> q;
    q.push(s);
    visit[s] = 1;
    pre[s] = -1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v=0; v<V; v++)
        {
            if (visit[v]==0 && rGraph[u][v] > 0)
            {
                q.push(v);
                pre[v] = u;
                visit[v] = 1;
            }
        }
    }
    return (visit[t] == 1);
}

void Ford(int graph[V][V], int s, int t)
{
    int u, v;
    stack <int> stack;
    int rGraph[V][V]; 
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
             rGraph[u][v] = graph[u][v];
             //这个矩阵存储当前流量

    int pre[V]; 
    int max_flow=0;
    while (bfs(rGraph, s, t, pre))
    {   
        // for (int i = 0; i < 7; ++i)
        // {
        //    cout << pre[i] << "\t";
        // }cout <<endl;
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=pre[v])
        {//取得当前流中最小的限制
            u = pre[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        
        for (v=t; v!=s; v=pre[v])
        {//根当前的可行流修改矩阵
            u = pre[v];
            rGraph[u][v] -= path_flow;//相当于占用资源
            rGraph[v][u] += path_flow;
            stack.push(u+1);//为输出做准备
        } stack.pop();cout << "S -> ";
        for (int i = 0; !stack.empty(); ++i)
        {
            cout << stack.top() << " -> ";
            stack.pop();
        }//输出当前可行流
        cout <<"T\tpathflow:"<<path_flow<<endl;
        max_flow+=path_flow;//最大流
    }

    cout << "maximum flow : "<< max_flow << endl;

    return;
}

int main()
{
                     // {S, 2, 3, 4, 5, 6, T},
    int graph[V][V] = { {0, 13, 9, 0, 0, 0, 0}, //S
                        {0, 0, 0, 6, 5, 0, 0},  //2
                        {0, 4, 0, 5, 0, 5, 0},  //3
                        {0, 0, 0, 0, 5, 4, 4},  //4
                        {0, 0, 0, 0, 0, 0, 9},  //5
                        {0, 0, 0, 0, 0, 0, 10}, //6
                        {0, 0, 0, 0, 0, 0, 0}   //T
                      };
    Ford(graph, 0, 6);
    system("pause");
    return 0;
}