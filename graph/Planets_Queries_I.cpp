// Used Binary Jumping for finding nth parent
// use ll only when it is required
// else better to use int

#include <bits/stdc++.h>
#include <thread>
using namespace std;
 
#define ll long long int
#define ff first
#define ss second
#define all(v) v.begin(), v.end()
 
// Required For Shortest Path in Graph
#define MAXLL numeric_limits<ll>::max()
#define MINLL numeric_limits<ll>::min()
#define MOD (ll)(1e9 + 7)
 
// Required For Dijkstra Algorithm
#define max_heap priority_queue<ll>
#define min_heap priority_queue<ll, vector<ll>, greater<ll>>

const int MAXN = 2e5 + 5; // Max Nodes in a Graph
const int MAXD = 30; // Max parent Depth 2 ^ 30 = 1e9
int parent[MAXN][MAXD];
 
 
void find_all_cycles(vector<vector<ll>> &G, ll u, ll p, vector<ll> &color, vector<bool> &vis, vector<ll> &par, vector<vector<ll>> &cycles, bool is_undirected){
	if(color[u] == 2){
		return;
	}
	if(color[u] == 1){
		ll cur = p;
		vector<ll> v;
		v.push_back(cur);
		while(cur != u){
			cur = par[cur];
			v.push_back(cur);
		}
		cycles.push_back(v);
		return;
	}
	color[u] = 1;
	par[u] = p;
	vis[u] = 1;
	for(auto v : G[u]){
		if(is_undirected && v == par[u]){
			continue;
		}
		find_all_cycles(G, v, u, color, vis, par, cycles, is_undirected);
	}
	color[u] = 2;
}
 
void detect_and_find_all_cycles(vector<vector<ll>> &G, bool &is_undirected, vector<vector<ll>> &cycles){
	ll n = G.size();
	vector<ll> color(n, 0);
	vector<bool> vis(n, 0);
	vector<ll> par(n, -1);
	for(ll i = 1; i < n; ++i){
		if(!vis[i]){
			find_all_cycles(G, i, -1, color, vis, par, cycles, is_undirected);
		}
	}
}
 
void dfs(vector<vector<ll>> &G, vector<bool> &vis, ll src, ll par, queue<ll> &Q){
	vis[src] = 1;
	Q.push(src);
	for(auto adj : G[src]){
		if(par != adj && !vis[adj]){
			dfs(G, vis, adj, src, Q);
		}
	}
}

// Binary Jumping
int jump(int a, int d) {
	for (int i = 0; i < MAXD; i++)
		if (d & (1ll << i)) a = parent[a][i];
	return a;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, q;
	cin >> n >> q;
	for(int i = 1; i <= n; ++i){
		cin >> parent[i][0];
	}
	for(int i = 1; i < MAXD; ++i){
		for(int j = 1; j <= n; ++j){
			parent[j][i] = parent[parent[j][i - 1]][i - 1];
		}
	}
	while(q--){
		int v, k;
		cin >> v >> k;
		cout << jump(v, k) << endl;
	}
	return 0;
}
