#include <cstdio>
#include <cctype>
#include <algorithm>
const int maxn=100005;
int N,mp[maxn],id[maxn];
inline void read(int &Res){
	char ch=getchar();
	for (Res=0;!isdigit(ch);ch=getchar());
	for (;isdigit(ch);ch=getchar()) Res=(Res<<3)+(Res<<1)+ch-48;
}
struct Ad{
	int num,id;
	inline int operator < (const Ad &c) const{
		if (num^c.num) return num<c.num;
		return id<c.id;
	}
}A[maxn];
struct SplayTree{
	int root,tot,pre[maxn],ch[maxn][2],size[maxn];
	bool rev[maxn];
	//pre[]表示父亲节点，rev[]表示翻转标记
	inline void Clear(){
		rev[size[pre[root=tot=0]=0]=0]=0,ch[0][0]=ch[1][0]=0;
	}
	inline void pushdown(int x){
		if (rev[x]) rev[ch[x][0]]^=1,rev[ch[x][1]]^=1,std::swap(ch[x][0],ch[x][1]),rev[x]=0;
	}
	inline void pushup(int x){
		size[x]=size[ch[x][0]]+size[ch[x][1]]+1;
	}
	inline void Create(int &p,int fa){
		pre[p=++tot]=fa,ch[p][0]=ch[p][1]=rev[p]=0,size[p]=1;
	}
	inline void rotate(int x,bool t){
		int y=pre[x]; pushdown(y),pushdown(x);
		ch[y][t^1]=ch[x][t]; if (ch[x][t]) pre[ch[x][t]]=y;
		pre[x]=pre[y]; if (pre[y]) ch[pre[y]][ch[pre[y]][1]==y]=x;
		pre[ch[x][t]=y]=x,pushup(y);
	}//Splay旋转时节点编号无法改变（传入的又不是在树里的元素，改变了也没用），这和SBT有区别
	//0 LEFT
	//1 RIGHT
	inline void Splay(int x,int fa){
		//伸展树的精髓Zig&Zag
		for (pushdown(x);pre[x]^fa;){
			int y=pre[x],z=pre[y];
			pushdown(z),pushdown(y),pushdown(x);
			if (z==fa) rotate(x,ch[pre[x]][1]^x); else{
				if (ch[z][0]==y){
					if (ch[y][0]==x) rotate(y,1),rotate(x,1);
						else rotate(x,0),rotate(x,1);
				} else{
					if (ch[y][0]==x) rotate(x,1),rotate(x,0);
						else rotate(y,0),rotate(x,0);
				}
			}
		}
		pushup(x);
		if (!fa) root=x;
	}
	inline void Select(int k,int fa){
		int x=root;
		while (1){
			pushdown(x);
			 if (k==size[ch[x][0]]+1) break;
			 if (k<=size[ch[x][0]]) x=ch[x][0]; else k-=size[ch[x][0]]+1,x=ch[x][1];
		}
		Splay(x,fa);
	}
	inline void Deroot(){
		int tmp=root;
		if (ch[root][1]){
			root=ch[root][1],Select(1,0),ch[root][0]=ch[tmp][0];
			//把右子树中序遍历的第一个点旋转到根（因为这个点的左儿子肯定为空）
			//将原先根节点的左子树接到当前根节点的左子树上
			if (ch[tmp][0]) pre[ch[tmp][0]]=root;
		} else root=ch[root][0];
		pre[root]=0,pushup(root);
	}
	inline void Build(int &p,int L,int R,int fa){
		if (L>R) return; int mid=(L+R)>>1;
		Create(p,fa),mp[id[mid]]=p,Build(ch[p][0],L,mid-1,p),Build(ch[p][1],mid+1,R,p),pushup(p);
	}
	inline void Solve(){
		Clear(),mp[id[1]]=1,mp[id[N]]=2,Create(root,0),Create(ch[root][1],root),Build(ch[ch[root][1]][0],2,N-1,ch[root][1]),pushup(ch[root][1]),pushup(root);
		for (int i=1;i<=N;++i)
			Splay(mp[i],0),printf("%d",i+size[ch[root][0]]),putchar(i<N?' ':'\n'),rev[ch[root][0]]^=1,Deroot();
	}
}T;
int main(){
	freopen("HDU1890.in","r",stdin),freopen("HDU1890.out","w",stdout);
	while (scanf("%d",&N),N){
		if (N==1){scanf("%*d"),puts("1"); continue;}
		for (int i=1;i<=N;++i) read(A[A[i].id=i].num);
		std::sort(A+1,A+1+N);
		for (int i=N;i;--i) id[A[i].id]=i;
		T.Solve();
	}
	return 0;
}
