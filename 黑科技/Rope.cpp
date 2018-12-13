/*
 * rope test;
 * test.push_back(x); //在末尾添加x
 * test.insert(pos,x); //在pos位置插入x
 * test.erase(pos,x); //从pos开始删除x个
 * test.copy(pos,len,x); //从pos开始到pos+len为止用x代替
 * test.replace(pos,x); //从pos开始换乘x
 * test.substr(pos,x); //从pos开始提取x个
 * test.at(x); //访问第x个元素
 * test[x]; 访问第x个元素
 * 算法复杂度为n^(3/2),可以在很短的时间内实现快速的插入,删除和查找字符串,是一个很厉害的神器！
 */
#include<bits/stdc++.h>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
rope<int> a;
int main() {
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;++i) a.push_back(i);
    while(m--) {
        int pos,s;
        cin>>pos>>s;
        pos--;
        a=a.substr(pos,s)+a.substr(0,pos)+a.substr(pos+s,n-pos-s);
    }
    for(int i=0;i<n;++i) cout<<a[i]<<" ";
    cout<<"\n";
    return 0;
}
