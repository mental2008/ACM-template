/*
 * 读入时候这样写:
 * int x;
 * FastIO::Read(x);
 * 
 * 若要处理到文件末尾可以这样写：
 * while(FastIO::Read(x), FastIO::IOError == 0);
 */
#include<cstdio>
namespace FastIO {
	#define BUF_SIZE 10000000 //缓冲区大小可修改
	bool IOError = 0; //IOError == false 时表示处理到文件结尾
	inline char NextChar() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if(pend == p1) {
				IOError = 1;
				return -1;
			}
		}
		return *p1++;
	}
	inline bool Blank(char c) {
		return c == ' ' || c == '\n' || c == '\r' || c == '\t';
	}

	template<class T> inline void Read(T &x) {
		char c;
		while(Blank(c = NextChar()));
		if(!IOError) {
			for(x = 0; '0' <= c && c <= '9'; c = NextChar())
				x = (x << 3) + (x << 1) + c - '0';
		}
	}
}