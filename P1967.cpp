#include <bits/stdc++.h>
using namespace std;

int n,m;
int h[10005],from[100005],to[100005],nx[100005],w[100005],et=2;
int bcj[10005],edge[100005];
int roots[10005];
int th[10005],tto[20005],tnx[20005],tw[20005],tet=2;
int fa[10005][15],max_w[10005][15];

inline void add_edge(int u,int v,int _w) {
    to[et]=v;
    from[et]=u;
    w[et]=_w;
    nx[et]=h[u];
    h[u]=et++;
}

inline void tadd_edge(int u,int v,int _w) {
    tto[tet]=v;
    tw[tet]=_w;
    tnx[tet]=h[u];
    th[u]=tet++;
}

inline bool cmp(int a,int b) {
    return (w[a]>w[b]);
}

inline int bcjfind(int x) {
    if (bcj[x]==x) {
        return x;
    }
    bcj[x]=bcj[bcj[x]];
    return bcjfind(bcj[x]);
}

inline bool merge(int x,int y) {
    if (bcjfind(x)!=bcjfind(y)) {
        bcj[bcjfind(y)]=bcjfind(x);
        return true;
    }
    return false;
}

inline void kruskal() {
    for (int i=1;i<=n;i++) {
        bcj[i]=i;
    }
    for (int i=0;i<m;i++) {
        edge[i]=(i<<1)+2;
    }
    sort(edge,edge+m,cmp);
    for (int i=0;i<m;i++) {
        if (merge(from[i],to[i])) {
            tadd_edge(from[i],to[i],w[i]);
            tadd_edge(to[i],from[i],w[i]);
        }
    }
    for (int i=1;i<=n;i++) {
        roots[find(i)]=find(i);
    }
}

inline void _lcainit(int root,int father,int _w) {
    if (father==-1) {
        for (int i=0;i<15;i++) fa[root][i]=root,max_w[root][i]=INT_MAX;
    }else {
        fa[root][0]=father;
        max_w[root][0]=_w;
        for (int i=1;i<15;i++) fa[root][i]=fa[fa[root][i-1]][i-1],max_w[root][0]=min(max_w[root][i-1],max_w[fa[root][i-1]][i-1]);
    }
    for (int i=th[root];i;i=tnx[i]) {
        if (to[i]!=father) _lcainit(to[i],root,tw[i]);
    }
}

void lcainit() {
    for (int i=1;i<=n;i++) {
        if (roots[i]) {
            _lcainit(i);
        }
    }
}

int main() {
    cin>>n>>m;
    int x,y,z;
    for (int i=0;i<m;i++) {
        cin>>x>>y>>z;
        add_edge(x,y,z);
        add_edge(y,x,z);
    }
    kruskal();
    lcainit();
}
