// 查询静态区间第k小

#include<bits/stdc++.h>

using namespace std;

#define mem(a,i) memset(a,i,sizeof(a))
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=a;i>=b;--i)
typedef long long ll;
const int maxn=2e5+5;
int a[maxn];
int b[maxn];
int rt[maxn];
int sum[maxn*32];
int L[maxn*32];
int R[maxn*32];
int cnt;
int build(int l,int r) {
    int root=++cnt;
    sum[root]=0;
    if(l==r) return root;
    int mid=(l+r)>>1;
    L[root]=build(l,mid);
    R[root]=build(mid+1,r);
    return root;
}
int update(int pre,int l,int r,int x) {
    int root=++cnt;
    L[root]=L[pre];
    R[root]=R[pre];
    sum[root]=sum[pre]+1;
    if(l==r) return root;
    int mid=(l+r)>>1;
    if(x<=mid) L[root]=update(L[pre],l,mid,x);
    else R[root]=update(R[pre],mid+1,r,x);
    return root;
}
int query(int u,int v,int l,int r,int k) {
    if(l==r) return l;
    int x=sum[L[v]]-sum[L[u]];
    int mid=(l+r)>>1;
    if(x>=k) return query(L[u],L[v],l,mid,k);
    else return query(R[u],R[v],mid+1,r,k-x);
}

int main() {
    int n,q;
    scanf("%d%d",&n,&q);
    rep(i,1,n) {
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    int m=unique(b+1,b+n+1)-b-1;
    cnt=0;
    rt[0]=build(1,m);
    rep(i,1,n) {
        int t=lower_bound(b+1,b+m+1,a[i])-b;
        rt[i]=update(rt[i-1],1,m,t);
    }
    while(q--) {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        int ans=query(rt[x-1],rt[y],1,m,z);
        printf("%d\n",b[ans]);
    }
    return 0;
}

/*
 * hdu 4348
 * 操作C，对[l,r]区间加上d，同时时间戳后移
 * 操作Q，查询t时刻，[l,r]区间和
 * 操作H，查询当前时刻，[l,r]区间和
 * 操作B，回退到时刻t
 */

#include<bits/stdc++.h>

using namespace std;

#define mem(a,i) memset(a,i,sizeof(a))
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=a;i>=b;--i)
typedef long long ll;
const int maxn=1e5+5;
int n,q;
int rt[maxn];
int L[maxn*40];
int R[maxn*40];
ll sum[maxn*40];
ll add[maxn*40];
ll a[maxn];
int cnt;
int build(int l,int r) {
    int root=++cnt;
    add[root]=0;
    if(l==r) {
        sum[root]=a[l];
        return root;
    }
    int mid=(l+r)>>1;
    L[root]=build(l,mid);
    R[root]=build(mid+1,r);
    sum[root]=sum[L[root]]+sum[R[root]];
    return root;
}
int update(int pre,int l,int r,int ql,int qr,int d) {
    int root=++cnt;
    L[root]=L[pre];
    R[root]=R[pre];
    add[root]=add[pre];
    sum[root]=sum[pre];
    if(l>=ql&&r<=qr) {
        add[root]+=d;
        sum[root]+=(ll)d*(r-l+1);
        return root;
    }
    int mid=(l+r)>>1;
    if(ql<=mid) L[root]=update(L[pre],l,mid,ql,qr,d);
    if(qr>mid) R[root]=update(R[pre],mid+1,r,ql,qr,d);
    sum[root]=sum[L[root]]+sum[R[root]]+add[root]*(r-l+1);
    return root;
}
ll query(int root,int l,int r,int ql,int qr) {
    if(l>=ql&&r<=qr) return sum[root];
    ll res=0;
    if(l<=ql) {
        if(r>=qr) res+=add[root]*(qr-ql+1);
        else res+=add[root]*(r-ql+1);
    }
    else {
        res+=add[root]*(qr-l+1);
    }
    int mid=(l+r)>>1;
    if(ql<=mid) res+=query(L[root],l,mid,ql,qr);
    if(qr>mid) res+=query(R[root],mid+1,r,ql,qr);
    return res;
}

int main() {
    while(~scanf("%d%d",&n,&q)) {
        cnt=0;
        rep(i,1,n) scanf("%lld",&a[i]);
        rt[0]=build(1,n);
        int time=0;
        while(q--) {
            char o[5];
            scanf("%s",o);
            if(o[0]=='C') {
                time++;
                int l,r,d;
                scanf("%d%d%d",&l,&r,&d);
                rt[time]=update(rt[time-1],1,n,l,r,d);
            }
            else if(o[0]=='Q') {
                int l,r;
                scanf("%d%d",&l,&r);
                ll ans=query(rt[time],1,n,l,r);
                printf("%lld\n",ans);
            }
            else if(o[0]=='H') {
                int l,r,t;
                scanf("%d%d%d",&l,&r,&t);
                ll ans=query(rt[t],1,n,l,r);
                printf("%lld\n",ans);
            }
            else {
                int t;
                scanf("%d",&t);
                time=t;
            }
        }
    }
    return 0;
}
