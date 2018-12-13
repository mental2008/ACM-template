#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
__gnu_pbds::priority_queue<int,greater<int> > a,b; //小的优先
__gnu_pbds::priority_queue<int> c; //大的优先
int main() {
    a.push(2);a.push(5);
    b.push(4);b.push(1);
    a.join(b);
    cout<<a.top()<<"\n";
    return 0;
}
// output: 1