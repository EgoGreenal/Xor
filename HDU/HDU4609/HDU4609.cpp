#include <cstdio>
#include <cctype>
#include <cstring>
#include <complex>
#include <algorithm>
#include <cmath>
using namespace std;
typedef complex<double> cp;
typedef long long ll;
const int maxn=262155;
const double PI=acos(-1.0);
int T,N,M,Bit,tmp,rev[maxn],hsh[maxn],P[maxn];
cp A[maxn]; ll sum[maxn],Ans;
inline void Make_Rev(int N,int Bit){
	for (int i=0;i<N;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(Bit-1));
}
inline void FFT(cp *A,int N,int DFT){
	for (int i=0;i<N;++i) if (i<rev[i]) swap(A[i],A[rev[i]]);
	cp Wn,WnK,x,y;
	for (int Step=1;Step<N;Step<<=1){
		Wn=exp(cp(0,DFT*PI/Step));
		for (int j=0;j<N;j+=Step<<1){
			WnK=cp(1,0);
			for (int k=j;k<j+Step;++k,WnK*=Wn)
				x=A[k],y=WnK*A[k+Step],A[k]=x+y,A[k+Step]=x-y;
		}
	}
	if (DFT<0) for (int i=0;i<N;++i) A[i]/=N;
}
inline void read(int &Res){
	char ch=getchar();
	for (Res=0;!isdigit(ch);ch=getchar());
	for (;isdigit(ch);ch=getchar()) Res=(Res<<3)+(Res<<1)+ch-48;
}
int main(){
	freopen("HDU4609.in","r",stdin),freopen("HDU4609.out","w",stdout);
	for (read(T);T--;){
		read(M),memset(A,0,sizeof A),memset(hsh,0,sizeof hsh),memset(sum,0,sizeof sum),Ans=0;
		for (int i=0;i<M;++i) read(P[i]),++hsh[P[i]]; sort(P,P+M),tmp=P[M-1]<<1|1;
		for (int i=P[M-1];i;--i) A[i]=hsh[i];
		for (N=2,Bit=1;N<tmp;N<<=1,++Bit);
		Make_Rev(N,Bit),FFT(A,N,1);
		for (int i=0;i<N;++i) A[i]*=A[i];
		FFT(A,N,-1);
		for (int i=0;i<N;++i) sum[i]=(ll)(A[i].real()+0.5);
		for (int i=0;i<M;++i) --sum[P[i]<<1];
		for (int i=N-1;~i;--i) (sum[i]>>=1)+=sum[i+1];
		for (int i=0;i<M;++i) Ans+=sum[P[i]+1]-(ll)(M-1-i)*i-((ll)(M-1-i)*(M-2-i)>>1)-(M-1);
		printf("%.7lf\n",6.0*Ans/M/(M-1)/(M-2));
	}
	return 0;
}
