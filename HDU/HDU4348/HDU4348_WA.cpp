#include <cstdio>
#include <cctype>
#include <cstring>
const int maxn=100005,maxp=3000005;
typedef long long ll;
template<typename _Tp> inline void read(_Tp &Res){
	char ch=getchar(); int fl=0;
	for (Res=0;!isdigit(ch);ch=getchar()) fl^=(ch=='-');
	for (;isdigit(ch);ch=getchar()) Res=(Res<<3)+(Res<<1)+ch-48;
	if (fl) Res=(~Res)+1;
}
int N,M,x,y,z,Now_T;
char con;
struct PT{
	int Root[maxn],x,y,len,tmp; ll z;
	struct Node{int l,r; ll sum,addv;}T[maxp];
	inline void Clear(){len=0,memset(Root,0,sizeof Root);}
	inline void Pushdown(int p,int L,int R){
		if (T[p].addv){
			tmp=(L+R)>>1;
			T[++len]=T[T[p].l],T[len].sum+=T[p].addv*(tmp-L+1),T[len].addv+=T[p].addv,T[p].l=len;
			T[++len]=T[T[p].r],T[len].sum+=T[p].addv*(R-tmp),T[len].addv+=T[p].addv,T[p].r=len;
			T[p].addv=0;
		}
	}
	void Build(int &p,int L,int R){
		T[++len]=T[p],p=len;
		if (L>=R){read(T[p].sum),T[p].addv=0; return;}
		int mid=(L+R)>>1;
		Build(T[p].l,L,mid),Build(T[p].r,mid+1,R);
		T[p].sum=T[T[p].l].sum+T[T[p].r].sum,T[p].addv=0;
	}
	void Update(int &p,int L,int R){
		T[++len]=T[p],p=len;
		if (x<=L&&R<=y){
			T[p].sum+=z*(R-L+1),T[p].addv+=z;
			return;
		}
		Pushdown(p,L,R);
		int mid=(L+R)>>1;
		if (x<=mid) Update(T[p].l,L,mid);
		if (y>mid) Update(T[p].r,mid+1,R);
		T[p].sum=T[T[p].l].sum+T[T[p].r].sum;
	}
	inline void Modify(int _tm,int L,int R,ll num){
		x=L,y=R,z=num,Update(Root[_tm]=Root[_tm-1],1,N);
	}
	void Query(int p,int L,int R){
		if (x<=L&&R<=y){
			z+=T[p].sum;
			return;
		}
		Pushdown(p,L,R);
		int mid=(L+R)>>1;
		if (x<=mid) Query(T[p].l,L,mid);
		if (y>mid) Query(T[p].r,mid+1,R);
	}
	inline ll GetAns(int _tm,int L,int R){
		x=L,y=R,z=0,Query(Root[_tm],1,N);
		return z;
	}
}T;
int main(){
	freopen("HDU4348.in","r",stdin),freopen("HDU4348.out","w",stdout);
	while (~scanf("%d%d",&N,&M)){
		for (T.Clear(),T.Build(T.Root[0],1,N),Now_T=0;M--;){
			do con=getchar(); while (!isalpha(con));
			read(x);
			if (con^'B') read(y);
			if (con=='H'||con=='C') read(z);
			switch (con){
				case 'Q':printf("%lld\n",T.GetAns(Now_T,x,y)); break;
				case 'C':T.Modify(++Now_T,x,y,z); break;
				case 'H':printf("%lld\n",T.GetAns(z,x,y)); break;
				case 'B':T.len=T.Root[1+(Now_T=x)]-1; break;
			}
		}
		puts("");
	}
	return 0;
}
