/* 
 * 适用于正负整数 (包括int,long long与__int128)
 */
template<typename T>
inline bool Read(T &r) {
	char c;
	int sgn;
	if(c=getchar(),c==EOF) return 0; // EOF
	while(c!='-'&&(c<'0'||c>'9')) c=getchar();
	sgn=(c=='-')?-1:1;
	r=(c=='-')?0:(c-'0');
	while(c=getchar(),c>='0'&&c<='9') r=r*10+(c-'0');
	return r*sgn;
}
template<typename T>
inline void out(T x) {
	if(x>9) out(x/10);
	putchar(x%10+'0');
}