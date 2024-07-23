// Use Bellman Ford Algorithm and DFS

#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define ff first
#define ss second
#define INF numeric_limits<ll>::max()
#define NINF numeric_limits<ll>::min()


void dfs(vector<vector<ll>> &G, ll src, vector<bool>&vis){
	vis[src] = 1;
	for(auto it : G[src]){
		if(!vis[it]){
			dfs(G, it, vis);
		}
	}
}

int main() {
	ll n, m;
	cin >> n >> m;
	vector<tuple<ll, ll, ll>> edges;
	vector<vector<ll>> G1(n + 1);
	vector<vector<ll>> G2(n + 1);
	for(ll i = 0; i < m; ++i){
		ll u, v, w;
		cin >> u >> v >> w;
		tuple<ll, ll, ll> t = make_tuple(u, v, -w);
		edges.push_back(t);
		G1[u].push_back(v);
		G2[v].push_back(u);
	}
	vector<ll> d(n + 1, INF);
	d[1] = 0;
	for(ll i = 1; i <= (n - 1); ++i){
		for(auto it : edges){
			ll u, v, w;
			tie(u, v, w) = it;
			if(d[u] != INF && d[u] + w < d[v]){
				d[v] = d[u] + w;
			}
		}
	}
	vector<bool> vis1(n + 1, 0);
	vector<bool> vis2(n + 1, 0);
	dfs(G1, 1, vis1);
	dfs(G2, n, vis2);
	for(auto it : edges){
		ll u, v, w;
		tie(u, v, w) = it;
		if(d[u] + w < d[v] && vis1[u] && vis2[v]){
			cout << -1 << endl;
			return 0;
		}
	}
	cout << d[n] * -1 << endl;
	return 0;
}