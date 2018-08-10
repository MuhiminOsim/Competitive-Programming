#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define SZ 100005

ll n;
ll sz[SZ];
char ans[SZ];
bool black[SZ];
vector <ll> adj[SZ];

void getSize(ll pos, ll par){
    sz[pos]=1;
    for(int i=0;i<adj[pos].size();i++){
        ll v=adj[pos][i];
        if(black[v] || v==par) continue;
        getSize(v,pos);
        sz[pos]+=sz[v];
    }
}

ll getCenter(ll pos, ll par, ll szz){
    for(int i=0;i<adj[pos].size();i++){
        ll v=adj[pos][i];
        if(black[v] || v==par) continue;
        if(2*sz[v]>szz) return getCenter(v,pos,szz);
    }
    return pos;
}

ll Center(ll pos){
    getSize(pos,0);
    return getCenter(pos,0,sz[pos]);
}

void decompose(ll pos, char ch){
    ll newCenter = Center(pos);
    black[newCenter]=1;
    ans[newCenter]=ch;
    char next=(char)(ch+1);
    for(int i=0;i<adj[newCenter].size();i++){
        ll v=adj[newCenter][i];
        if(black[v]) continue;
        decompose(v,next);
    }
}
int main()
{
    cin>>n;
    for(int i=0;i<n-1;i++){
        ll u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    decompose(1,'A');
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
    cout<<endl;
    return 0;
}
