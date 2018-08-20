#include <cstdio>
#include <vector>
using namespace std;
#define ll long long
#define root 0
#define LOGN 14
#define mx 10100
vector <ll> adj[mx],costs[mx],index[mx];
ll baseArray[mx],chainIndex[mx],chainHead[mx],posInBase[mx];
ll depth[mx],parent[LOGN][mx],otherEnd[mx],subsize[mx];
ll segTree[mx*6],queTree[mx*6],ptr,chainNo;

void buildTree(ll pos,ll L,ll R){
    if(L==R-1){
        segTree[pos]=baseArray[L];
        return;
    }
    ll mid=(L+R)>>1;
    ll pos1=(pos<<1),pos2=pos1|1;
    buildTree(pos1,L,mid);
    buildTree(pos2,mid,R);
    segTree[pos]=segTree[pos1]>segTree[pos2]?segTree[pos1]:segTree[pos2];
}

void updateTree(ll pos, ll L, ll R, ll x, ll val){
    if(L>x || R<=x) return;
    if(L==R-1){
        segTree[pos]=val;
        return;
    }
    ll mid=(L+R)>>1;
    ll pos1=(pos<<1),pos2=pos1|1;
    updateTree(pos1,L,mid,x,val);
    updateTree(pos2,mid,R,x,val);
    segTree[pos]=segTree[pos1]>segTree[pos2]?segTree[pos1]:segTree[pos2];
}

void queryTree(ll pos, ll L, ll R, ll l, ll r){
    if(L>=r || R<=l){
        queTree[pos]=-1;
        return;
    }
    if(L>=l && R<=r){
        queTree[pos]=segTree[pos];
        return;
    }
    ll mid=(L+R)>>1;
    ll pos1=(pos<<1),pos2=pos1|1;
    queryTree(pos1,L,mid,l,r);
    queryTree(pos2,mid,R,l,r);
    queTree[pos]=queTree[pos1]>queTree[pos2]?queTree[pos1]:queTree[pos2];
}

ll queryUp(ll u,ll v){
    if(u==v) return 0;
    ll uchain,vchain=chainIndex[v],ans=-1;
    while(true){
        uchain=chainIndex[u];
        if(uchain==vchain){
            if(u==v) break;
            queryTree(1,0,ptr,posInBase[v]+1,posInBase[u]+1);
            ans=max(ans,queTree[1]);
            break;
        }
        queryTree(1,0,ptr,posInBase[chainHead[uchain]],posInBase[u]+1);
        ans=max(ans,queTree[1]);
        u=chainHead[uchain];
        u=parent[0][u];
    }
    return ans;
}

ll LCA(ll u,ll v){
    if(depth[u]<depth[v]) swap(u,v);
    ll diff=depth[u]-depth[v];
    for(int i=0;i<LOGN;i++) if((diff>>i)&1) u=parent[i][u];
    if(u==v) return u;
    for(int i=LOGN-1;i>=0;i--){
        if(parent[i][u]!=parent[i][v]){
            u=parent[i][u];
            v=parent[i][v];
        }
    }
    return parent[0][u];
}

void query(ll u, ll v){
    ll lca=LCA(u,v);
    ll ans=queryUp(u,lca);
    ans=max(ans,queryUp(v,lca));
    printf("%lld\n",ans);
}

void change(ll idx, ll val){
    ll u=otherEnd[idx];
    updateTree(1,0,ptr,posInBase[u],val);
}

void HLD(ll curNode, ll cost, ll par){
    if(chainHead[chainNo]==-1){
        chainHead[chainNo]=curNode;
    }
    chainIndex[curNode]=chainNo;
    posInBase[curNode]=ptr;
    baseArray[ptr++]=cost;
    ll heavyChild=-1,ncost;
    for(int i=0;i<adj[curNode].size();i++){
        if(adj[curNode][i]!=par){
            if(heavyChild==-1 || subsize[heavyChild]<subsize[adj[curNode][i]]){
                heavyChild=adj[curNode][i];
                ncost=costs[curNode][i];
            }
        }
    }
    if(heavyChild!=-1) HLD(heavyChild,ncost,curNode);
    for(int i=0;i<adj[curNode].size();i++){
        if(adj[curNode][i]!=par){
            if(heavyChild!=adj[curNode][i]){
                chainNo++;
                HLD(adj[curNode][i],costs[curNode][i],curNode);
            }
        }
    }
}

void dfs(ll cur, ll par, ll level=0){
    parent[0][cur]=par;
    depth[cur]=level;
    subsize[cur]=1;
    for(int i=0;i<adj[cur].size();i++){
        if(adj[cur][i]!=par){
            otherEnd[index[cur][i]]=adj[cur][i];
            dfs(adj[cur][i],cur,level+1);
            subsize[cur]+=subsize[adj[cur][i]];
        }
    }
}

int main(){
    ll t;
    scanf("%lld",&t);
    while(t--){
        ptr=0;
        ll n;
        scanf("%lld",&n);
        for(int i=0;i<n;i++){
            adj[i].clear();
            costs[i].clear();
            index[i].clear();
            chainHead[i]=-1;
            for(int j=0;j<LOGN;j++) parent[j][i]=-1;
        }
        for(int i=1;i<n;i++){
            ll u,v,cost;
            scanf("%lld %lld %lld",&u,&v,&cost);
            u--; v--;
			adj[u].push_back(v);
			costs[u].push_back(cost);
			index[u].push_back(i-1);
			adj[v].push_back(u);
			costs[v].push_back(cost);
			index[v].push_back(i-1);
        }
        chainNo=0;
        dfs(root,-1);
        HLD(root,-1,-1);
        buildTree(1,0,ptr);
        for(int i=1;i<LOGN;i++){
            for(int j=0;j<n;j++){
                if(parent[i-1][j]!=-1){
                    parent[i][j]=parent[i-1][parent[i-1][j]];
                }
            }
        }
        while(true){
            char str[100];
            scanf("%s",str);
            if(str[0]=='D') break;
            ll u,v;
            scanf("%lld %lld",&u,&v);
            if(str[0]=='Q') query(u-1,v-1);
            else change(u-1,v);
        }
    }
    return 0;
}
