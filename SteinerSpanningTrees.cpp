#include <iostream>
#include <bits/stdc++.h>
using namespace std;

bool check(vector<bool> &seen,vector<int> &T){
    for(auto it:T){
        if(seen[it]==false)
            return false;
    }
    return true;
}
                                                          //vertex,weight
vector<vector<pair<int,int>>> Prim_Modified(vector<vector<pair<int,int>>> &adj,vector<int> &T){
    int V = adj.size();
    int s = T[0];
    vector<bool> seen(V,false);
    vector<int> d(V,INT_MAX);

    //contain three values -> value,self, parent
    priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>> pq;

    // it will contain a stiner minimum spanning tree
    vector<vector<pair<int,int>>>stiner;
    stiner.assign(V,vector<pair<int,int>>());

    pq.push({0,s,-1});
    
    int n = V-1;
    while(n-- && !check(seen,T)){
        auto x = pq.top(); //x = {val,self,parent}
        pq.pop();
        seen[x[1]]=true;
        //cout<<x[1]<<" "<<x[2]<<" "<<x[0]<<"\n";
        //push into the stiner
        if(x[2]!=-1){
            stiner[x[2]].push_back({x[1],x[0]});
            stiner[x[1]].push_back({x[2],x[0]});
        }
        
        //go to every adjacent vertex
        for(auto it: adj[x[1]]){
            int v = it.first;
            int w = it.second;
            if(seen[v])continue;
            if(d[v]>w){
                d[v] = w;
                //weigh , adj, self
                pq.push({w,v,x[1]});
            }
        }
    }

    return stiner;
}

void print(vector<vector<pair<int,int>>>&adj){
    int V = adj.size();
    for(int i=0;i<V;i++){
        cout<<i<<"->";
        for(auto it: adj[i]){
            int v = it.first;
            int w = it.second;
            cout<<"{"<<v<<","<<w<<"}";
        }
        cout<<"\n";
    }
}

bool lie(vector<int> &T,int v){
    for(int i=0;i<T.size();i++){
        if(T[i]==v)
            return true;
    }

    return false;
}

int main()
{

    int V,E;
    cout<<"Enter the vertex and edges respectively: ";
    cin>>V>>E;
    vector<vector<pair<int,int>>>adj(V,vector<pair<int,int>>());
    vector<int> T;
    
    
    vector<vector<pair<int,int>>>stiner;
    int u,v,w;


    for(int i=0;i<E;i++){
        cout<<"Enter an u,v,w: ";
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});  
    }

    cout<<"\nThe adjanceney list is:\n";
    print(adj);
    int t;

    cout<<"\nEnter the number of vertices in spanning tree: ";
    cin>>t;

    cout<<"Enter the vertices: ";
    for(int i=0;i<t;i++){
        int temp;cin>>temp;
        T.push_back(temp);
    }

    for(auto it:T)
        cout<<it<<" ";
    cout<<"\n";

    stiner = Prim_Modified(adj,T);

    // print(stiner);

    vector<int> degree(V,0);

    //find the degree of vertices
    for(int i=0;i<V;i++){
        for(auto it:stiner[i]){
            degree[i]++;
        }
    }

    vector<bool> removingVertex(V,false);
    queue<int> q;

    for(int i=0;i<V;i++){
        //cout<<degree[i]<<" ";
        if(!lie(T,i) && degree[i]==1)
            q.push(i);
    }
    cout<<"\n";



    while(!q.empty()){
        removingVertex[q.front()]=true;
        for(auto it:adj[q.front()]){
            int v = it.first;
            int w = it.second;
            degree[v]--;
            if(degree[v]==1 && !lie(T,v)){
                q.push(v);
            }
        }
        q.pop();
    }

    // for(int i=0;i<V;i++){
    //     cout<<removingVertex[i]<<" ";
    // }
    cout<<"\n";
    //modifire stiner spanning tree
    vector<vector<pair<int,int>>>modifierStiner(V,vector<pair<int,int>>());
    for(int i=0;i<V;i++){
        if(removingVertex[i])continue;
        for(auto it:stiner[i]){
            if(removingVertex[it.first])continue;
            modifierStiner[i].push_back(it);
        }
    }

    // print(modifierStiner);
    for(int i=0;i<V;i++){
        if(!modifierStiner[i].size())continue;
        cout<<i<<"->";
        for(auto it: modifierStiner[i]){
            int v = it.first;
            int w = it.second;
            cout<<"{"<<v<<","<<w<<"}";
        }
        cout<<"\n";
    }

    return 0;

}
