// id starts with 1
namespace QuerySubtree{
    static const int N = ::N;
    int sz[N] , wson[N] , par[N];
    void dfs(int c,int fa,vi g[]){
        sz[c]=1;par[c]=fa;int &s=wson[c]=0;
        for(auto t:g[c]) if(t!=fa)
            dfs(t,c,g),sz[c]+=sz[t],(sz[t]>=sz[s])&&(s=t);
    }
  	vi nd;
    void solve(int c,int fa,bool iswson,vi g[]){
        for(auto t : g[c]) if(t != wson[c] && t != fa) solve(t , c , false , g);
        if(wson[c]) solve(wson[c] , c , true , g);
        for(auto t : g[c]) if(t != wson[c] && t != fa) {
            // ������������Ϣ����
        }
      	// ����ǰ�ڵ����Ϣ����
      	// ��ѯ
        if(!iswson) {
        	// ɾ��������������Ϣ nd.clear()
        }
    }
    void solve(vi g[]){
        dfs(1,0,g);
        solve(1,0,false,g); // ��������ǵ������ݣ��ĳ� true �����Ż�
    }
}
