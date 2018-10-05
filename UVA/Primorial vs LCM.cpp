#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mx 10000002
#define m 1000000007
#define pb push_back
#define ff first
#define ss second

ll prime[mx],k,vis[mx],tst,n,ans;
vector <pair<ll,ll> > v;
void sieve()
{
    prime[k++]=2;
    for(int i=4;i<mx;i+=2) vis[i]=1;
    for(int i=3;i*i<mx;i+=2){
        if(!vis[i]){
            for(int j=i*i;j<mx;j+=2*i){
                vis[j]=1;
            }
        }
    }
    for(int i=3;i<mx;i+=2) if(!vis[i]) prime[k++]=i;
}

bool cmp(ll v, pair<ll,ll> p){
    if(p.first>v) return true;
    return false;
}

void preprocess()
{
    for(int i=0;i<k;i++){
        ll x=1;
        while(x<=1e14/prime[i]){
            x*=prime[i];
            if(x!=prime[i]) v.pb({x,prime[i]});
        }
    }
    sort(v.begin(),v.end());
    for(int i=1;i<v.size();i++){
        //cout<<v[i].ff<<" "<<v[i].ss<<endl;
        v[i].ss=(v[i].ss%m*v[i-1].ss%m)%m;
    }
    //for(int i=0;i<v.size();i++) cout<<v[i].ff<<" "<<v[i].ss<<endl;
}

ll bigmod(ll x, ll y){
    ll ret=1;
    x%=m;
    while(y){
        if(y&1) ret=(ret*x)%m;
        y=y>>1;
        x=(x*x)%m;
    }
    return ret;
}

int main()
{
    sieve();
    preprocess();
    scanf("%lld",&tst);
    for(int t=1;t<=tst;t++){
        scanf("%lld",&n);
        ll x=upper_bound(v.begin(),v.end(),n,cmp)-v.begin();
        x--;
        if(x>=0) ans=v[x].ss;
        else ans=1;
        printf("Case %d: %lld\n",t,ans);
    }
    return 0;
}
