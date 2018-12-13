/*
 * fact[i], i的阶乘
 * fiv[i], i的阶乘的逆元
 * inv[i], i的逆元
 */
typedef long long ll;
const int maxn=1e5+5;
const int mod=1e9+7;
ll fact[maxn];
ll fiv[maxn];
ll inv[maxn];
void init() {
    fact[0]=fact[1]=1;
    fiv[0]=fiv[1]=1;
    inv[1]=1;
    for(int i=2;i<maxn;++i) {
        fact[i]=fact[i-1]*i%mod;
        inv[i]=inv[mod%i]*(mod-mod/i)%mod;
        fiv[i]=fiv[i-1]*inv[i]%mod;
    }
}