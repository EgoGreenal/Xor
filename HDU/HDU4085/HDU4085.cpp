#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
const int maxn=55,maxe=2005,maxl=1035,inf=0x3f3f3f3f;
int T,N,M,K,Alo,hd,tl,lnk[maxn],nxt[maxe],son[maxe],w[maxe],s[maxn],F[maxn][maxl],g[maxl],tot;
struct Ad{int id,opt;}que[52505],k;
bool vis[maxn][maxl];
inline void read(int &Res){
	char ch=getchar();
	for (Res=0;!isdigit(ch);ch=getchar());
	for (;isdigit(ch);ch=getchar()) Res=(Res<<3)+(Res<<1)+ch-48; 
}
inline void Add(int x,int y,int z){
	nxt[++tot]=lnk[x],son[lnk[x]=tot]=y,w[tot]=z;
}
inline void Spfa(){
	while (hd^tl){
		k=que[++hd],vis[k.id][k.opt]=0;
		for (int j=lnk[k.id];j;j=nxt[j]) if (F[k.id][k.opt]+w[j]<F[son[j]][k.opt|s[son[j]]]){
			F[son[j]][k.opt|s[son[j]]]=F[k.id][k.opt]+w[j];
			if (k.opt==(k.opt|s[son[j]])&&!vis[son[j]][k.opt]){
				vis[son[j]][k.opt]=1,que[++tl]=(Ad){son[j],k.opt};
				if (F[son[j]][k.opt]<F[que[hd+1].id][que[hd+1].opt]) std::swap(que[hd+1],que[tl]);
			}
		}
	}
}
inline bool check(int opt){
	int Ret=0;
	for (int i=0;opt;++i,opt>>=1) if (opt&1) Ret+=i<K?1:-1;
	return !Ret;
}
int main(){
	freopen("HDU4085.in","r",stdin),freopen("HDU4085.out","w",stdout);
	for (scanf("%d",&T);T;--T){
		read(N),read(M),read(K),memset(vis,0,sizeof vis),memset(s,0,sizeof s),memset(lnk,0,sizeof lnk),tot=0,memset(F,63,sizeof F);
		for (int i=M,x,y,z;i;--i) read(x),read(y),read(z),Add(x,y,z),Add(y,x,z);
		for (int i=K;i;--i) F[i][s[i]=1<<(i-1)]=0,F[N-i+1][s[N-i+1]=1<<(K+i-1)]=0;
		Alo=1<<(K<<1);
		for (int S=0;S<Alo;++S){
			hd=tl=0;
			for (int j=N;j;--j){
				for (int i=(S-1)&S;i;i=(i-1)&S) F[j][S]=std::min(F[j][S],F[j][i|s[j]]+F[j][(S-i)|s[j]]);
				if (F[j][S]<inf) que[++tl]=(Ad){j,S},vis[j][S]=1;
			}
			Spfa();
		}
		for (int S=0;S<Alo;++S){
			g[S]=inf;
			for (int i=N;i;--i) g[S]=std::min(g[S],F[i][S]);
		}
		for (int S=1;S<Alo;++S) if (check(S))
			for (int i=(S-1)&S;i;i=(i-1)&S) if (check(i)) g[S]=std::min(g[S],g[S-i]+g[i]);
		if (g[Alo-1]<inf) printf("%d\n",g[Alo-1]); else puts("No solution");
	}
	return 0;
}
