#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll VMAX = ll(1e5+1);
ll depth[VMAX];

//up[i][j] gives the 2^j the ancestor of i
//Here at max j can be log of the depth of the tree. Because:
/* Suppose depth of the tree is 100:
    Now available powers of two: 1,2,4,8...64 
    Using only these we can reach 100

    Suppose you want to jump 15 times up from vertex 3:
    so every number can be written in powers of two(binary representation)
    15 = 1111 = 1 + 2 + 4 + 8
    so we do up[up[up[ up[3][0] ][1]][2]][3]
*/

//Here I take it to be log(n)


ll up[VMAX][20];
ll parent[VMAX];
int seen[VMAX];
vector <ll> adj[VMAX];
int n;

// To reach 2 ancestor of a node we have up[u][1]
//So to reach 4 th ancestor of the same node we can go its 2nd ancestor and then second ansector of that anscestor
//up[v][2] = up[up[v][1]][1];

//Time complexity: O(nlogn)
void dfs(int u){
    seen[u] = 1;
    for(auto s: adj[u]){
        if(seen[s]) continue;
        up[s][0] = u;
        depth[s] = 1 + depth[u];
        parent[s] = u;
        seen[s] = 1;
        //Now that we reached ancestors of s in dfs style we have already visited its anscestors
        //Hence we can do this
        for(int j=1;j<20;j++){
            up[s][j] = up[up[s][j-1]][j-1];
        }
        dfs(s);
    }
}

ll lca(ll a, ll b){
    if(depth[a]<depth[b]){
        swap(a,b);
    }
    //Now a is always with higher depth se we move it up to the level of b in powers of two;
    int k = depth[a] - depth[b]; 
    for(int i=19;i>=0;i--){
        if(k & (1<<i)){
            a = up[a][i];
        }
    }
    //Now a and b are at the same level
    //This if is necessary as if a and b were equal a is the lca but in our last return we would
    //return its parent
    if(a==b){
        return a;
    }

    //Here we see if we move to a same node , then it could be the lca or lca can be even lower
    //So when we dont find node to be equal on a jump, we move them up to get a and b closest to
    //lca
    for(int i=19;i>=0;i--){
        if(up[a][i]!=up[b][i]){
            a=up[a][i];
            b=up[b][i];
        }
    }

    return up[a][0];
}

//Using the above dfs we can preprocess up array in O(nlogn)
int main(){

    memset(parent, -1, sizeof parent);
    memset(seen , 0, sizeof seen);
    memset(depth,0, sizeof depth);
    cin>>n;
    ll a,b;
    for(int i=0;i<n-1;i++){
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1);
    // for(int i=1;i<=n;i++){
    //     for(int j=0;j<20;j++){
    //         cout<<i<<" "<<j<<" "<<up[i][j]<<endl;
    //     }
    // }
    cout<<lca(4,5)<<endl;
    cout<<lca(5,2)<<endl;
}