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
int N,M,x,y,t,Now_T;
char con; ll v;
//该线段树的写法仅仅是为了节省空间，但因较难监测，不可持久时一般不采用
struct PT{
	int Root[maxn],len,x,y; ll z;
	struct Node{int l,r; ll lz,sum;}T[maxp];
	inline void Clear(){len=0,memset(Root,0,sizeof Root);}
	void Build(int &p,int L,int R){
		T[++len]=T[p],T[p=len].lz=0;
		if (L>=R){read(T[p].sum); return;}
		int mid=(L+R)>>1;
		Build(T[p].l,L,mid),Build(T[p].r,mid+1,R);
		T[p].sum=T[T[p].l].sum+T[T[p].r].sum;
	}
	void Update(int &p,int L,int R){
		T[++len]=T[p],T[p=len].sum+=z*((y<R?y:R)-(x>L?x:L)+1);
		if (x<=L&&R<=y){T[p].lz+=v; return;}
		int mid=(L+R)>>1;
		if (x<=mid) Update(T[p].l,L,mid);
		if (y>mid) Update(T[p].r,mid+1,R);
	}
	void Query(int p,int L,int R){
		if (x<=L&&R<=y){z+=T[p].sum; return;}
		z+=T[p].lz*((y<R?y:R)-(x>L?x:L)+1);
		int mid=(L+R)>>1;
		if (x<=mid) Query(T[p].l,L,mid);
		if (y>mid) Query(T[p].r,mid+1,R);
	}
	inline void Modify(int L,int R,ll k){
		x=L,y=R,z=k,Update(Root[++Now_T]=Root[Now_T-1],1,N);
	}
	inline ll GetAns(int _tm,int L,int R){
		x=L,y=R,z=0,Query(Root[_tm],1,N);
		return z;
	}
	inline void SetTime(int _tm){
		len=Root[(Now_T=_tm)+1]-1;
	}
}T;
int main(){
	freopen("HDU4348.in","r",stdin),freopen("HDU4348.out","w",stdout);
	while (~scanf("%d%d",&N,&M)){
		for (T.Clear(),T.Build(T.Root[0],1,N),Now_T=0;M--;){
			do con=getchar(); while (!isalpha(con));
			switch (con){
				case 'Q':read(x),read(y),printf("%lld\n",T.GetAns(Now_T,x,y)); break;
				case 'C':read(x),read(y),read(v),T.Modify(x,y,v); break;
				case 'H':read(x),read(y),read(t),printf("%lld\n",T.GetAns(t,x,y)); break;
				case 'B':read(t),T.SetTime(t);
			}
		}
	}
	return 0;
}
