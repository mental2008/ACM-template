// 整数 (int, long long)
template<typename T>
void Read(T &r){
	char c;
	while(c=getchar()){
		if(isdigit(c)){
			r=c^0x30;break;
		}
	}
	while(isdigit(c=getchar()))
		r=r*10+(c^0x30);
}