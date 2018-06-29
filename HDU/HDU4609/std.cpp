#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define Pi acos(-1)
using namespace std;

int n,a[400010],r[400010],l,maxx,limit;
long long sum[400010],cnt[400010];
struct comp
{
    double r,i;
    comp() {}
    comp(double a,double b):r(a),i(b) {}
} num[400010];

inline comp operator +(const comp a,const comp b)
{
    return comp(a.r+b.r,a.i+b.i);
}

inline comp operator -(const comp a,const comp b)
{
    return comp(a.r-b.r,a.i-b.i);
}

inline comp operator *(const comp a,const comp b)
{
    return comp(a.r*b.r-a.i*b.i,a.i*b.r+a.r*b.i);
}

void FFT(comp *a,int kd)
{
    for(int i=0; i<limit; i++)
    {
        if(i<r[i])
        {
            swap(a[i],a[r[i]]);
        }
    }
    for(int mid=1; mid<limit; mid<<=1)
    {
        comp wn=comp(cos(Pi/mid),kd*sin(Pi/mid));
        for(int l=mid<<1,j=0; j<limit; j+=l)
        {
            comp w=comp(1.0,0.0);
            for(int k=0; k<mid; k++,w=w*wn)
            {
                comp u=a[k+j];
                comp v=w*a[k+j+mid];
                a[k+j]=u+v;
                a[k+j+mid]=u-v;
            }
        }
    }
}

int main()
{
	freopen("HDU4609.in","r",stdin),freopen("GG.out","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        limit=1;
        l=0,maxx=0;
        for(int i=0; i<n; i++)
        {
            scanf("%d",&a[i]);
            maxx=max(maxx,a[i]);
        }
        sort(a,a+n);
        while(limit<=maxx*2)
        {
            limit<<=1;
            l++;
        }
        for(int i=0; i<limit; i++)
        {
            r[i]=r[i>>1]>>1|(i&1)<<(l-1);
            num[i].r=num[i].i=0.0;
        }
        for(int i=0; i<n; i++)
        {
            num[a[i]].r+=1.0;
        }
        FFT(num,1);
        for(int i=0; i<limit; i++)
        {
            num[i]=num[i]*num[i];
        }
        FFT(num,-1);
        for(int i=0; i<limit; i++)
        {
            cnt[i]=(long long)(num[i].r/limit+0.5);
        }
        for(int i=0; i<n; i++)
        {
            cnt[a[i]<<1]--;
        }
        for(int i=0; i<limit; i++)
        {
            cnt[i]>>=1;
        }
        sum[0]=0;
        for(int i=1; i<limit; i++)
        {
            sum[i]=sum[i-1]+cnt[i];
        }
        long long ans=0;
        for(int i=0; i<n; i++)
        {
            ans+=sum[limit-1]-sum[a[i]];
            ans-=(n-1);
            ans-=(long long)(n-1-i)*i;
            ans-=(long long)(n-i-1)*(n-i-2)/2;
        }
        long long tot=(long long)n*(n-1)*(n-2)/6;
        printf("%.7lf\n",(double) ans/tot);
    }
}
