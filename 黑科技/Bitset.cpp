/*
 * 优化了空间复杂度和时间复杂度
 */
#include<bitset>
using namespace std;
bitset<length> b;
b[2] = 1; // 下标从0开始

常用函数
b1 = b2 & b3;
b1 = b2 | b3;
b1 = b2 ^ b3;
b1 = ~b2;
b1 = b2 << 3;

常用成员函数
b.any()         // b中是否存在置为1的二进制位?
b.none()        // b中不存在置为1的二进制位吗?
b.count()       // b中置为1的二进制位的个数
b.size()        // b中二进制位数的个数
b[pos]          // 访问b中在pos处的二进制位
b.test(pos)     // b中在pos处的二进制位置为1吗?
b.set()         // 把b中所有二进制位置为1
b.set(pos)      // 把b中在pos处的二进制位置为1
b.reset()       // 把b中所有二进制位置为0
b.reset(pos)    // 把b中在pos处的二进制位置为0
b.flip()        // 把b中所有二进制位逐位取反
b.flip(pos)     // 把b中在pos处的二进制位取反
b.to_ulong()    // 把b中同样的二进制位返回一个unsigned long
b.to_ullong()   // 把b中同样的二进制位返回一个unsigned long long