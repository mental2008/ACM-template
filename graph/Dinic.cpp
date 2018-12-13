#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2005;
const int INF=(1<<30)-1;
int n,m,s,t; //结点数，边数（包括反向弧），源点编号和汇点编号
struct Edge {
    int from,to,cap,flow;
    Edge(int _from,int _to,int _cap,int _flow) {
        from=_from,to=_to,cap=_cap,flow=_flow;
    }
};
vector<Edge> edges; //边表，edges[e]和edges[e^1]互为反向弧
vector<int> G[maxn]; //邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
bool vis[maxn]; //BFS使用
int d[maxn]; //从起点到i的距离
int cur[maxn]; //当前弧下标
void init() {
    for(int i=0;i<maxn;++i) G[i].clear();
    edges.clear();
}
void AddEdge(int from,int to,int cap) {
    edges.push_back(Edge(from,to,cap,0));
    edges.push_back(Edge(to,from,0,0));
    int k=edges.size();
    G[from].push_back(k-2);
    G[to].push_back(k-1);
}
bool BFS() {
    memset(vis,0,sizeof(vis));
    queue<int> Q;
    Q.push(s);
    d[s]=0;
    vis[s]=1;
    while(!Q.empty()) {
        int x=Q.front();
        Q.pop();
        for(int i=0;i<G[x].size();++i) {
            Edge e=edges[G[x][i]];
            if(!vis[e.to]&&e.cap>e.flow) { //只考虑残量网络中的弧
                vis[e.to]=1;
                d[e.to]=d[x]+1;
                Q.push(e.to);
            }
        }
    }
    return vis[t];
}
int DFS(int x,int a) {
    if(x==t||a==0) return a;
    int flow=0,f;
    for(int& i=cur[x];i<G[x].size();++i) { //从上次考虑的弧
        Edge& e=edges[G[x][i]];
        if(d[x]+1==d[e.to]&&(f=DFS(e.to,min(a,e.cap-e.flow)))>0) {
            e.flow+=f;
            edges[G[x][i]^1].flow-=f;
            flow+=f;
            a-=f;
            if(a==0) break;
        }
    }
    return flow;
}
int Maxflow(int u,int v) {
    s=u,t=v;
    int flow=0;
    while(BFS()) {
        memset(cur,0,sizeof(cur));
        flow+=DFS(u,INF);
    }
    return flow;
}