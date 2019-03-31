#include <bits/stdc++.h>
using namespace std;
#define ll int
#define pb push_back
#define ff first
#define ss second
#define mx 30004

ll n,q,pos;
pair <ll,ll> a[mx];
ll tree[4*mx],ans[200002];
struct queryArray{
    ll l,r,v,id;
    bool operator<(const queryArray& p){
        return v>p.v;
    }
}qy[200002];

void update(ll pos, ll l, ll r, ll idx, ll value){
    if(l==r && l==idx){
        tree[pos]=value;
        return;
    }
    ll mid=(l+r)/2;
    if(idx>=l && idx<=mid) update(pos*2,l,mid,idx,value);
    if(idx>=(mid+1) && idx<=r) update(pos*2+1,mid+1,r,idx,value);
    tree[pos]=tree[pos*2]+tree[pos*2+1];
}

ll query(ll pos, ll l, ll r, ll L, ll R){
    if(l>=L && r<=R) return tree[pos];
    if(r<L || l>R) return 0;
    ll mid=(l+r)/2;
    ll q1=query(pos*2,l,mid,L,R);
    ll q2=query(pos*2+1,mid+1,r,L,R);
    return q1+q2;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i].ff);
        a[i].ss=i;
    }
    sort(a+1,a+n+1);
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        scanf("%d %d %d",&qy[i].l,&qy[i].r,&qy[i].v);
        qy[i].id=i;
    }
    sort(qy+1,qy+q+1);
    pos=n;
    for(int i=1;i<=q;i++){
        while(pos>=1 && a[pos].ff>qy[i].v){
            update(1,1,n,a[pos].ss,1);
            pos--;
        }
        ans[qy[i].id]=query(1,1,n,qy[i].l,qy[i].r);
    }
    for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
    return 0;
}
