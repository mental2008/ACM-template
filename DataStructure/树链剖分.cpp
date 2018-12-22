/*
 * 原题
 * 操作①:将(u,v)路径上的所有点权都乘上x
 * 操作②:将(u,v)路径上的所有点权都加上x
 * 操作③:将(u,v)路径上的所有点权都进行二进制取反(实际上,等价于先乘上-1,再加上2^64-1)
 * 操作④:询问(u,v)路径上的点权和
 */
#include<bits/stdc++.h>

using namespace std;

#define mem(a,i) memset(a,i,sizeof(a))
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=a;i>=b;--i)
#define lowbit(x) (x&-x)
#define pb push_back
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
const int maxn=1e5+5;
vector<int> G[maxn];
int n;

int fa[maxn];
int depth[maxn];
int son[maxn];
int sz[maxn];
void dfs1(int u,int pre) {
    depth[u]=depth[pre]+1;
    fa[u]=pre;
    sz[u]=1;
    son[u]=0;
    int maxSon=-1;
    int len=(int)G[u].size();
    rep(i,0,len-1) {
        int v=G[u][i];
        if(v==pre) continue;
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[v]>maxSon) {
            maxSon=sz[v];
            son[u]=v;
        }
    }
}
int id[maxn];
int top[maxn];
int cnt;
void dfs2(int u,int topf) {
    id[u]=++cnt;
    top[u]=topf;
    if(!son[u]) return;
    dfs2(son[u],topf);
    int len=(int)G[u].size();
    rep(i,0,len-1) {
        int v=G[u][i];
        if(v==fa[u]||v==son[u]) continue;
        dfs2(v,v);
    }
}

ull seg[maxn*4];
ull addMark[maxn*4];
ull mulMark[maxn*4];
void build(int root,int l,int r) {
    seg[root]=0;
    addMark[root]=0;
    mulMark[root]=1;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(root<<1,l,mid);
    build(root<<1|1,mid+1,r);
}
void pushDown(int root,int l,int r) {
    int mid=(l+r)>>1;
    seg[root<<1]=seg[root<<1]*mulMark[root]+addMark[root]*(mid-l+1);
    seg[root<<1|1]=seg[root<<1|1]*mulMark[root]+addMark[root]*(r-mid);
    mulMark[root<<1]=mulMark[root<<1]*mulMark[root];
    mulMark[root<<1|1]=mulMark[root<<1|1]*mulMark[root];
    addMark[root<<1]=addMark[root<<1]*mulMark[root]+addMark[root];
    addMark[root<<1|1]=addMark[root<<1|1]*mulMark[root]+addMark[root];
    mulMark[root]=1;
    addMark[root]=0;
}
void update(int root,int l,int r,int ql,int qr,bool mul,ull val) {
    if(l>qr||r<ql) return;
    if(l>=ql&&r<=qr) {
        if(mul) {
            seg[root]*=val;
            mulMark[root]*=val;
            addMark[root]*=val;
        }
        else {
            addMark[root]+=val;
            seg[root]+=val*(r-l+1);
        }
        return;
    }
    pushDown(root,l,r);
    int mid=(l+r)>>1;
    update(root<<1,l,mid,ql,qr,mul,val);
    update(root<<1|1,mid+1,r,ql,qr,mul,val);
    seg[root]=seg[root<<1]+seg[root<<1|1];
}
ull query(int root,int l,int r,int ql,int qr) {
    if(l>qr||r<ql) return 0;
    if(l>=ql&&r<=qr) return seg[root];
    int mid=(l+r)>>1;
    pushDown(root,l,r);
    return query(root<<1,l,mid,ql,qr)+query(root<<1|1,mid+1,r,ql,qr);
}

void updRange(int x,int y,ull val,int o) {
    while(top[x]!=top[y]) {
        if(depth[top[x]]<depth[top[y]]) swap(x,y);
        if(o==1) update(1,1,n,id[top[x]],id[x],1,val);
        else if(o==2) update(1,1,n,id[top[x]],id[x],0,val);
        else {
            update(1,1,n,id[top[x]],id[x],1,~0ull);
            update(1,1,n,id[top[x]],id[x],0,~0ull);
        }
        x=fa[top[x]];
    }
    if(depth[x]>depth[y]) swap(x,y);
    if(o==1) update(1,1,n,id[x],id[y],1,val);
    else if(o==2) update(1,1,n,id[x],id[y],0,val);
    else {
        update(1,1,n,id[x],id[y],1,~0ull);
        update(1,1,n,id[x],id[y],0,~0ull);
    }
}
ull qRange(int x,int y) {
    ull ans=0;
    while(top[x]!=top[y]) {
        if(depth[top[x]]<depth[top[y]]) swap(x,y);
        ans+=query(1,1,n,id[top[x]],id[x]);
        x=fa[top[x]];
    }
    if(depth[x]>depth[y]) swap(x,y);
    ans+=query(1,1,n,id[x],id[y]);
    return ans;
}

int main() {
    while(~scanf("%d",&n)) {
        rep(i,1,n) G[i].clear();
        rep(i,1,n-1) {
            int u;
            scanf("%d",&u);
            G[u].pb(i+1);
            G[i+1].pb(u);
        }
        depth[0]=0;
        dfs1(1,0);
        cnt=0;
        dfs2(1,1);
        build(1,1,n);
        int m;
        scanf("%d",&m);
        while(m--) {
            int o,u,v;
            scanf("%d%d%d",&o,&u,&v);
            if(o==1) {
                ull x;
                scanf("%llu",&x);
                updRange(u,v,x,1);
            }
            else if(o==2) {
                ull x;
                scanf("%llu",&x);
                updRange(u,v,x,2);
            }
            else if(o==3) {
                updRange(u,v,0,3);
            }
            else {
                ull ans=qRange(u,v);
                printf("%llu\n",ans);
            }
        }
    }
    return 0;
}