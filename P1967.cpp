#include <bits/stdc++.h>
using namespace std;

int n,m,q,x,y;
int h[10005],from[100005],to[100005],nx[100005],w[100005],et=2;
int bcj[10005],edge[100005];
int roots[10005];
int th[10005],tto[20005],tnx[20005],tw[20005],tet=2;
int fa[10005][15],max_w[10005][15],dep[10005];

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
    tnx[tet]=th[u];
    th[u]=tet++;
}

inline bool cmp(int a,int b) {
    return (w[a]>w[b]);
}

inline int find(int x) {
    if (bcj[x]==x) {
        return x;
    }
    bcj[x]=bcj[bcj[x]];
    return find(bcj[x]);
}

inline bool merge(int x,int y) {
    if (find(x)!=find(y)) {
        bcj[find(y)]=find(x);
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
        if (merge(from[edge[i]],to[edge[i]])) {
            tadd_edge(from[edge[i]],to[edge[i]],w[edge[i]]);
            tadd_edge(to[edge[i]],from[edge[i]],w[edge[i]]);
        }
    }
    for (int i=1;i<=n;i++) {
        roots[find(i)]=find(i);
    }
}

inline void _lcainit(int root,int father,int _w,int depth) {
    //if (dep[root]) return;
    dep[root]=depth;
    if (father==-1) {
        for (int i=0;i<15;i++) fa[root][i]=root,max_w[root][i]=INT_MAX;
    }else {
        fa[root][0]=father;
        max_w[root][0]=_w;
        for (int i=1;i<15;i++) fa[root][i]=fa[fa[root][i-1]][i-1],max_w[root][i]=min(max_w[root][i-1],max_w[fa[root][i-1]][i-1]);
    }
    for (int i=th[root];i;i=tnx[i]) {
        if (tto[i]!=father) _lcainit(tto[i],root,tw[i],depth+1);
    }
}

void lcainit() {
    for (int i=1;i<=n;i++) {
        if (roots[i]) {
            _lcainit(i,-1,INT_MAX,1);
        }
    }
}

int lca(int a,int b) {
    if (find(a)!=find(b)) return -1;
    int weight=INT_MAX;
    if (dep[a]<dep[b]) {
        swap(a,b);
    }
    int offset=dep[a]-dep[b];
    for (int i=0;offset;offset>>=1,i++) {
        if (offset&1) {
            weight=min(weight,max_w[a][i]);
            a=fa[a][i];
        }
    }
    for (int i=14;i>=0;i--) {
        if (fa[a][i]!=fa[b][i]) {
            weight=min(weight,max_w[a][i]);
            a=fa[a][i];
            weight=min(weight,max_w[b][i]);
            b=fa[b][i];
        }
    }
    weight=min(weight,max_w[b][0]);
    weight=min(weight,max_w[a][0]);
    return weight;
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
    cin>>q;
    for (int i=0;i<q;i++) {
        cin>>x>>y;
        cout<<lca(x,y)<<endl;
    }
    return 0;
}
