#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define prime 3
#define mod 1000

int main()
{
    ll hashing[mod]= {0};
    string str,q;
    cin>>str;
    while(true)
    {
        cin>>q;
        if(q.size()>str.size()){
            cout<<"Doesn't exist"<<endl;
            continue;
        }
        ll tmp=0;
        for(int i=str.size()-q.size(),j=0;i<str.size();i++,j++){
            tmp+=((ll)str[i]*powl(prime,j));
            tmp+=mod;
            tmp%=mod;
        }
        hashing[tmp]++;
        for(int i=str.size()-q.size()-1; i>=0; i--)
        {
            tmp*=prime;
            tmp+=(ll)str[i];
            tmp-=((ll)str[i+q.size()]*powl(prime,q.size()));
            tmp+=powl(mod,q.size());
            tmp%=mod;
            hashing[tmp]++;
        }
        ll qhash=0;
        for(int i=0; i<q.size(); i++)
        {
            qhash+=((ll)q[i]*powl(prime,i));
            qhash+=mod;
            qhash%=mod;
        }
        if(hashing[qhash])
            cout<<"Exists!"<<endl;
        else
            cout<<"Doesn't exist"<<endl;
    }
    return 0;
}
