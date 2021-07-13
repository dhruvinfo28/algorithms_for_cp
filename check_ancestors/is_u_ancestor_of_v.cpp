#include<bits/stdc++.h>
using namespace std;

//We will do a dfs from the root and mark in-time and out-time of every node from the dfs
//So if an anscestor will have a lesser intime and a greater outime then the descendant

const int max_ = 20;
vector<int> adj[max_];
int inTime[max_];
int outTime[max_];
bool seen[max_];

void dfs(int u, int &count){
    seen[u] = true;
    inTime[u] = ++count;
    for(auto s: adj[u]){
        if(!seen[s])
            dfs(s,count);
    }
    outTime[u] = ++count;
}

void preProcess(){
    memset(inTime,0,sizeof inTime);
    memset(outTime, 0, sizeof outTime);
    memset(seen,false,sizeof seen);
    int cnt = 0;
    dfs(0,cnt);
}

bool check_ancestor(int u, int v){
    return inTime[u]<=inTime[v] && outTime[u]>=outTime[v];
}

int main(){
    int n; cin>>n;
    // vector <int> adj[n];
    int a,b;
    for(int i=0;i<n-1;i++){
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    preProcess();
    cout<<check_ancestor(1,6)<<endl;
    cout<<check_ancestor(1,7)<<endl;
}