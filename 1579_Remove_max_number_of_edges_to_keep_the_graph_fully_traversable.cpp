class DSU{
 public:
 vector<int> sz,par;
 //DSU constructor
 DSU(int n){
    sz.resize(n+2,1);
    par.resize(n+2,1);
    for(int i=1;i<=n;i++){
        par[i]=i;
    }
 }

 int findupar(int v){
    if(par[v]==v)return v;

    return par[v]=findupar(par[v]);
 }

 void unionbysize(int u,int v){
    int upar=findupar(u);
    int vpar=findupar(v);
    if(upar==vpar)return;

    if(sz[upar]>sz[vpar]){
        par[vpar]=upar;
        sz[upar]+=sz[vpar];
    }
    else{
        par[upar]=vpar;
        sz[vpar]+=sz[upar];
    }
 }


};


class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        vector<vector<int>> alice,bob,both;
        // alice and bob jyare use karvan , jyare both no pohchi shake
        
        for(int i=0;i<edges.size();i++){
           if(edges[i][0]==1){
              alice.push_back({edges[i][1],edges[i][2]});
           }
           else if(edges[i][0]==2){
               bob.push_back({edges[i][1],edges[i][2]});
           }
           else{
              both.push_back({edges[i][1],edges[i][2]});
           }
        }

        DSU ds1(n+2),ds2(n+2);
        int extra=0;

        for(auto &val:both){
            int u=val[0],v=val[1];
            if(ds1.findupar(u)==ds1.findupar(v)){
                extra++;
            }
            else{
                ds1.unionbysize(u,v);
                ds2.unionbysize(u,v);
            }
        }
        for(auto &val:alice){
            int u=val[0],v=val[1];
            if(ds1.findupar(u)==ds1.findupar(v)){
                extra++;
            }
            else{
                ds1.unionbysize(u,v);
            }
        }
        for(auto &val:bob){
            int u=val[0],v=val[1];
            if(ds2.findupar(u)==ds2.findupar(v)){
                extra++;
            }
            else{
                ds2.unionbysize(u,v);
            }
        }
        

        unordered_map<int,int>  mp1,mp2;
        for(int i=1;i<=n;i++){
            mp1[ds1.findupar(i)]++;
            mp2[ds2.findupar(i)]++;
        }
        if(mp1.size()>1 || mp2.size()>1)return -1;
        // cout<<mp1.size()<<"\n";
        // cout<<mp2.size()<<"\n";
        return extra;
    }
};