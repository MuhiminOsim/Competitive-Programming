#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 150005
int tree[4*MAX];
int a[MAX];

void update(int pos, int L, int R, int p,  int value){
    if(L>p || R< p) return;
    if(p>=L && p<=R){
        tree[pos]+=value;
        if(L==R) return;
    }
    int mid=(L+R)/2;
    update(pos*2, L, mid, p, value);
    update(pos*2+1, mid+1, R, p, value);
}
int query(int pos,int L, int R,int p){
    if(L==R){
        return L;
    }
    int k=tree[pos*2];
    int mid=(L+R)/2;
    if(k>=p) return query(pos*2,L,mid,p);
    else return query((pos*2)+1,mid+1,R,p-k);
}
int main()
{
    int tst,n,q,p,k,nq,pos;
    char ch[10];
    scanf("%d",&tst);
    for(int t=1;t<=tst;t++){
        scanf("%d %d",&n,&q);
        k=n;
        nq=n+q;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        memset(tree,0,sizeof(tree));
        //build(1,1,n);
        for(int i=1;i<=n;i++){
            update(1,1,nq,i,1);
        }
        printf("Case %d:\n",t);
        while(q--){
            scanf("%s %d",&ch,&p);
            if(ch[0]=='c'){
                if(p>n) printf("none\n");
                else{
                    n--;
                    pos=query(1,1,nq,p);
                    printf("%d\n", a[pos]);
                    update(1,1,nq,pos,-1);
                }
            }
            else{
                n++;
                k++;
                a[k]=p;
                update(1,1,nq,k,1);
            }
        }
    }
    return 0;
}
