#include<bits/stdc++.h>

// Main condition to notice was that there is only one outgoing edge
// Then we can use topological Sort to find cycles
// And then count nodes in cycle

class Solution {
public:
    
    void dfs(int v,vector<int> &vis,vector<vector<int>> &g,int &cnt){
         cnt++;
         vis[v]=1;

        for(auto &val:g[v]){
            if(vis[val]==0)dfs(val,vis,g,cnt);
        }
    }
  
    int longestCycle(vector<int>& edges) {
        int n=edges.size();
        queue<int> q;
        vector<int> indegree(n+1,0);
        vector<vector<int>> g(n);
        
        for(int i=0;i<edges.size();i++){
            if(edges[i]==-1)continue;
            g[i].push_back(edges[i]);
            indegree[edges[i]]++;
        }
        

        for(int i=0;i<n;i++){
            if(indegree[i]==0)q.push(i);
        }

        while(q.size()>0){
            int node=q.front();
            q.pop();
            for(auto &val: g[node]){
                indegree[val]--;
                if(indegree[val]==0)q.push(val);
            }
        }

        int sz=0;
        vector<int> vis(n+1,0);

        for(int i=0;i<n;i++){
            if(indegree[i]>0 && vis[i]==0){
                int cnt=0;
                dfs(i,vis,g,cnt);
                sz=max(sz,cnt);
            }
        }

        if(sz==0)return -1;

        return sz;


    }
};