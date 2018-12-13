/*
 * FWT(快速沃尔什变换)——解决多项式的位运算卷积
 * 能不取模尽量不取
 */
#include<bits/stdc++.h>

typedef long long ll;
const ll mod=1e9+7;
const ll inv2=(mod+1)>>1;
struct FWT {
    int N;
    void init(int n) {
        N=1;
        while(N<n) N<<=1;
    }
    void FWT_or(ll *a,int opt) {
        for(int i=1;i<N;i<<=1) {
            for(int p=i<<1,j=0;j<N;j+=p) {
                for(int k=0;k<i;++k) {
                    if(opt==1)
                        a[i+j+k]=(a[j+k]+a[i+j+k])%mod;
                    else
                        a[i+j+k]=(a[i+j+k]+mod-a[j+k])%mod;
                }
            }
        }
    }
    void FWT_and(ll *a,int opt) {
        for(int i=1;i<N;i<<=1) {
            for(int p=i<<1,j=0;j<N;j+=p) {
                for(int k=0;k<i;++k) {
                    if(opt==1)
                        a[j+k]=(a[j+k]+a[i+j+k])%mod;
                    else
                        a[j+k]=(a[j+k]+mod-a[i+j+k])%mod;
                }
            }
        }
    }
    void FWT_xor(ll *a,int opt) {
        for(int i=1;i<N;i<<=1) {
            for(int p=i<<1,j=0;j<N;j+=p) {
                for(int k=0;k<i;++k) {
                    ll x=a[j+k],y=a[i+j+k];
                    a[j+k]=(x+y)%mod;
                    a[i+j+k]=(x+mod-y)%mod;
                    if(opt==-1) {
                        a[j+k]=a[j+k]*inv2%mod;
                        a[i+j+k]=a[i+j+k]*inv2%mod;
                    }
                }
            }
        }
    }
} fwt;