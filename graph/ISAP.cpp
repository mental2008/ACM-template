#include<bits/stdc++.h>
using namespace std;
const int maxn=2005;
const int INF=(1<<30)-1;
// ISAP中的n非常重要，必须准确的定义为结点数，如有必要，建议将ISAP算法封装成一个结构体
int n,m,s,t; //结点数，边数（包括反向弧），源点编号和汇点编号
struct Edge {
    int from,to,cap,flow;
    Edge(int _from,int _to,int _cap,int _flow) {
        from=_from,to=_to,cap=_cap,flow=_flow;
    }
};
vector<Edge> edges; //边表，edges[e]和edges[e^1]互为反向弧
vector<int> G[maxn]; //邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
int p[maxn]; //可增广路上的上一条弧
int d[maxn]; //从起点到i的距离
int num[maxn]; //距离标号计数
bool vis[maxn]; //BFS使用
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
void BFS() {
    memset(vis,0,sizeof(vis));
    queue<int> Q;
    Q.push(t);
    vis[t]=1;
    d[t]=0;
    while(!Q.empty()) {
        int x=Q.front();
        Q.pop();
        for(int i=0;i<G[x].size();++i) {
            Edge e=edges[G[x][i]^1];
            if(!vis[e.from]&&e.cap>e.flow) {
                d[e.from]=d[x]+1;
                vis[e.from]=1;
                Q.push(e.from);
            }
        }
    }
}
int Augment() {
    int x=t,a=INF;
    while(x!=s) {
        Edge e=edges[p[x]];
        a=min(a,e.cap-e.flow);
        x=edges[p[x]].from;
    }
    x=t;
    while(x!=s) {
        edges[p[x]].flow+=a;
        edges[p[x]^1].flow-=a;
        x=edges[p[x]].from;
    }
    return a;
}
int Maxflow(int u,int v) {
    s=u,t=v;
    int flow=0;
    BFS();
    memset(num,0,sizeof(num));
    for(int i=0;i<=n;++i) num[d[i]]++;
    int x=s;
    memset(cur,0,sizeof(cur));
    while(d[s]<n) {
        if(x==t) {
            flow+=Augment();
            x=s;
        }
        int ok=0;
        for(int i=cur[x];i<G[x].size();++i) {
            Edge& e=edges[G[x][i]];
            if(e.cap>e.flow&&d[x]==d[e.to]+1) {
                ok=1;
                p[e.to]=G[x][i];
                cur[x]=i;
                x=e.to;
                break;
            }
        }
        if(!ok) { //Retreat
            int k=n-1;
            for(int i=0;i<G[x].size();++i) {
                Edge& e=edges[G[x][i]];
                if(e.cap>e.flow) k=min(k,d[e.to]);
            }
            if(--num[d[x]]==0) break; //gap优化
            num[d[x]=k+1]++;
            cur[x]=0;
            if(x!=s) x=edges[p[x]].from;
        }
    }
    return flow;
}