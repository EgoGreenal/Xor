#include <cstdio>
#include <cstdlib>
#include <windows.h>
int N;
int main(){
	freopen("HDU4609.in","w",stdout),srand(GetTickCount());
	puts("2");
	for (int k=0;k<2;++k){
		if (k) N=10; else N=1e5;
		printf("%d\n",N);
		for (int i=N;i;--i) printf("%d ",((rand()<<15)+rand())%N+1);
		putchar('\n');
	}
	return 0;
}
