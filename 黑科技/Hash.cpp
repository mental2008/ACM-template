/*
 * 头文件：
 * #include<ext/pb_ds/assoc_container.hpp>
 * #include<ext/pb_ds/hash_policy.hpp>
 * 用法：
 * cc_hash_table是拉链法
 * gp_hash_table是查探法
 * 除了当数组用外，还支持find和operator[]
 * 例如：__gnu_pbds::gp_hash_table<int,bool> h;
 */
#include<cstdio>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
__gnu_pbds::gp_hash_table<int,bool> h;

int main() {
    int n,m,k;
    scanf("%d%d",&n,&m);
    h.clear();
    while(n--) {
        scanf("%d",&k);
        h[k]=true;
    }
    while(m--) {
        scanf("%d",&k);
        puts(h[k]?"YES":"NO");
    }
    return 0;
}