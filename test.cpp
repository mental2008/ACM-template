#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn=2005;
const ll INF=0x3f3f3f3f3f3f3f3f;
int n,m,s,t;
struct Edge {
    int from,to;
    ll cap,flow;
    Edge(int _from,int _to,ll _cap,ll _flow) {
        from=_from,to=_to,cap=_cap,flow=_flow;
    }
};
vector<Edge> edges;
vector<int> G[maxn];
int p[maxn];
ll d[maxn];
int num[maxn];
bool vis[maxn];
int cur[maxn];
void init() {
    for(int i=0;i<maxn;++i) G[i].clear();
    edges.clear();
}
void AddEdge(int from,int to,ll cap) {
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
ll Augment() {
    int x=t;
    ll a=INF;
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
ll Maxflow(int u,int v) {
    s=u,t=v;
    ll flow=0;
    BFS();
    memset(num,0,sizeof(num));
    for(int i=0;i<maxn;++i) num[d[i]]++;
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
        if(!ok) {
            ll k=n-1;
            for(int i=0;i<G[x].size();++i) {
                Edge& e=edges[G[x][i]];
                if(e.cap>e.flow) k=min(k,d[e.to]);
            }
            if(--num[d[x]]==0) break;
            num[d[x]=k+1]++;
            cur[x]=0;
            if(x!=s) x=edges[p[x]].from;
        }
    }
    return flow;
}

int main() {
    init();
    int nn,mm;
    scanf("%d%d",&nn,&mm);
    n=nn+1;
    int s=0,t=nn+mm+1;
    for(int i=1;i<=nn;++i) {
        ll w;
        scanf("%lld",&w);
        AddEdge(i,t,w);
    }
    ll ans=0;
    for(int i=1;i<=mm;++i) {
        int u,v;
        ll w;
        scanf("%d%d%lld",&u,&v,&w);
        AddEdge(s,i+nn,w);
        AddEdge(i+nn,u,INF);
        AddEdge(i+nn,v,INF);
        ans+=w;
    }
    printf("%lld\n",ans-Maxflow(s,t));
}