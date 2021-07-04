//Lowest common ancestor in O(n) time:
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll VMAX = ll(1e5+1);

bool seen[VMAX];
ll depth[VMAX];
ll parent[VMAX];
vector <ll> adj[VMAX];

//Runs in O(n) for a tree 
void dfs(int u){
    seen[u] = true;
    for(auto s: adj[u]){
        if(seen[s]) continue;
        if(!seen[s]){
            depth[s] = 1 + depth[u];
            parent[s] = u;
            dfs(s);
        }
    }
}


ll get_lca(ll a, ll b){
    if(depth[a]<depth[b]){
        while(depth[a]!=depth[b]){
            b = parent[b];
        }
    }
    else{
        while(depth[a]!=depth[b]){
            a = parent[a];
        }
    }
    //Now both are at same depth
    //Move both of them equally
    while(a!=b){
        a = parent[a];
        b = parent[b];
    }
    return a;
}


//Application of an lca: Find distances between any two nodes in o(n)
//first calculate their LCA: then distance(u,v) = depth(u) + depth(v) + 2*depth(lca(u,v))
ll dist(ll a, ll b){
    ll lca = get_lca(a,b);
    return depth[a] + depth[b] - 2*depth[lca];
}


//Test case:
// 7
// 1 2
// 1 5
// 2 3
// 3 4
// 3 6
// 6 7

int main(){
    //Vertices:
    ll n; cin>>n;
    ll a,b; 
    //A tree will have n-1 edges
    for(int i=0;i<n-1;i++){
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    //Can take any node as the root:
    dfs(1);
    for(int i=1;i<=n;i++){
        cout<<"Depth("<<i<<"): "<<depth[i]<<" "<<"Parent("<<i<<"): "<<parent[i]<<endl;
    }
    cout<<endl;
    cout<<get_lca(4,3)<<endl;
    cout<<get_lca(4,5)<<endl;
    cout<<get_lca(2,5)<<endl;
    cout<<get_lca(4,7)<<endl;

    cout<<endl;
    cout<<dist(7,6)<<endl;
    cout<<dist(7,4)<<endl;
    cout<<dist(7,1)<<endl;
    cout<<dist(7,5)<<endl;
    
    return 0;
}

