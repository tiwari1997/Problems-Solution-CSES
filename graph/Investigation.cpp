// Use Dijkstra Algorithm
// Store graph as pair of adj, weight

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
 
 
bool directed_cyclic_util(vector<vector<ll>> &G, vector<bool> &color, ll src, vector<bool> &vis, ll p, vector<ll> &par, vector<vector<ll>> &all_cycles){
	if(all_cycles.size()){
		return true;
	}
	color[src] = 1;
	par[src] = p;
	vis[src] = 1;
	for(auto e : G[src]){
		if(color[e]){
			// Cycle Detected
			ll x = src;
			all_cycles.emplace_back();
			do{
				all_cycles.back().push_back(x);
				x = par[x];
			}while(x != e);
			all_cycles.back().push_back(e);
			reverse(all(all_cycles.back()));
			all_cycles.back().push_back(all_cycles.back()[0]);
			if(all_cycles[0].size() > 2){
				cout << all_cycles[0].size() << endl;
				for(auto ele : all_cycles[0]){
					cout << ele << " ";
				}
				cout << endl;
			}
			else{
				all_cycles.resize(0);
			}
			return true;
		}
		else if(color[e] == 0 && vis[e] == 0 && directed_cyclic_util(G, color, e, vis, src, par, all_cycles)){
			return true;
		}
	}
	color[src] = 0;
	return false;
}
 
void directed_cyclic(vector<vector<ll>> &G){
	ll n = G.size();
	vector<bool> color(n, 0);
	vector<bool> vis(n, 0);
	vector<ll> par(n, -1);
	vector<vector<ll>> all_cycles;
	for(ll i = 1; i < n; ++i){
		if(!vis[i]){
			if(directed_cyclic_util(G, color, i, vis, -1, par, all_cycles)){
				return;
			}
		}
	}
	// No Cycle Detected
	cout << "IMPOSSIBLE\n";
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
 
int main() {
	ll n, m;
	cin >> n >> m;
	vector<vector<pair<ll, ll>>> G(n + 1);
	vector<ll> mn(n + 1, 0);
	vector<ll> mx(n + 1, 0);
	vector<ll> cnt(n + 1, 0);
	for(ll i = 0; i < m; ++i){
		ll u, v, w;
		cin >> u >> v >> w;
		G[u].push_back({v, w});
	}
	vector<ll> dis(n + 1, MAXLL);
	vector<bool> vis(n + 1, 0);
	priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
	pq.push({0, 1});
	dis[1] = 0;
	cnt[1] = 1;
	while(pq.size()){
		ll u = pq.top().ss;
		pq.pop();
		if(vis[u]){
			continue;
		}
		vis[u] = 1;
		for(auto vc : G[u]){
			auto v = vc.ff;
			auto cost = vc.ss;
			if(dis[u] != MAXLL && dis[v] > (dis[u] + cost)){
				dis[v] = (dis[u] + cost);
				pq.push({dis[v], v});
				mn[v] = (mn[u] + 1);
				mx[v] = mx[u] + 1;
				cnt[v] = cnt[u];
			}
			else if(dis[u] != MAXLL && dis[v] == (dis[u] + cost)){
				mn[v] = min(mn[u] + 1, mn[v]);
				mx[v] = max(mx[u] + 1, mx[v]);
				cnt[v] = (cnt[v] + cnt[u]) % MOD;
			}
		}
	}
	cout << dis[n] << " " << cnt[n] << " " << mn[n] << " " << mx[n] << endl;
	return 0;
}
