
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<vector>
#include <ctime>
#include<queue>
#include<set>
#include<map>
#include<list>
#include<stack>
#include<iomanip>
#include<cmath>
#include<bitset>
#define mst(ss,b) memset((ss),(b),sizeof(ss))
///#pragma comment(linker, "/STACK:102400000,102400000")
typedef long long ll;
typedef long double ld;
#define INF (1ll<<60)-1
#define Max 30*100000
using namespace std;
int n,m;
ll a[100100];
struct node{
    ll sum,lazy;
    int l,r;
}tr[Max];
int tot=0;
void build(int &root,int l,int r){
    root=++tot;
    tr[root].l=l;
    tr[root].r=r;
    tr[root].lazy=0;
    if(l==r) {
        tr[root].sum=a[l];
        return ;
    }
    int mid=(l+r)/2;
    build(tr[root].l,l,mid);
    build(tr[root].r,mid+1,r);
    tr[root].sum=tr[tr[root].l].sum+tr[tr[root].r].sum;
}
void update(int &root,int l,int r,int last,int x,int y,ll v){
    root=++tot;
    tr[root]=tr[last];
    tr[root].sum+=1LL*(y-x+1)*v;
    //printf("root=%d l=%d r=%d sum=%I64d x=%d y=%d\n",root,tr[root].l,tr[root].r,tr[root].sum,x,y);
    if(x==l && y==r){
        tr[root].lazy+=v;
        return ;
    }
    int mid=(l+r)/2;
    if(y<=mid) update(tr[root].l,l,mid,tr[last].l,x,y,v);
    else if(x>mid) update(tr[root].r,mid+1,r,tr[last].r,x,y,v);
    else {
        update(tr[root].l,l,mid,tr[last].l,x,mid,v);
        update(tr[root].r,mid+1,r,tr[last].r,mid+1,y,v);
    }
}
ll query(int root,int l,int r,int x,int y){
    ll ans=tr[root].lazy*1LL*(y-x+1);
    //printf("root=%d l=%d r=%d sum=%I64d x=%d y=%d\n",root,tr[root].l,tr[root].r,tr[root].sum,x,y);
    if(x==l && y==r){
        return tr[root].sum;
    }
    int mid=(l+r)/2;
    if(y<=mid) ans+=query(tr[root].l,l,mid,x,y);
    else if(x>mid) ans+=query(tr[root].r,mid+1,r,x,y);
    else {
        ans+=query(tr[root].l,l,mid,x,mid);
        ans+=query(tr[root].r,mid+1,r,mid+1,y);
    }
    return ans;
}
int root[Max];
char s[110];
int main(){
	freopen("HDU4348.in","r",stdin),freopen("std.out","w",stdout);
    while(scanf("%d%d",&n,&m)!=EOF){
        tot=0;
        for(int i=1;i<=n;i++) scanf("%I64d",&a[i]);
        build(root[0],1,n);
        int now=0;
        for(int i=1;i<=m;i++){
            getchar();
            int x,y,t;
            ll v;
            scanf("%s",s);
            if(s[0]=='Q') {
                scanf("%d%d",&x,&y);
                printf("%I64d\n",query(root[now],1,n,x,y));
            } else if(s[0]=='C'){
                scanf("%d%d%I64d",&x,&y,&v);
                now++;
                update(root[now],1,n,root[now-1],x,y,v);
            } else if(s[0]=='H'){
                scanf("%d%d%d",&x,&y,&t);
                printf("%I64d\n",query(root[t],1,n,x,y));
            } else {
                scanf("%d",&t);
                now=t;
            }
        }
    }
    return 0;
}
