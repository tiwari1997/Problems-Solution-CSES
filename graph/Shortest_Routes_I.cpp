// Single Source Shortest Path Problem
// If weigths are not equal and >= 0, we should use Dijkstra Algorithm for Finding Shortest Path 
// Can be solved using Dijkstra since wights are not equal and non-negative (>= 0)
// Cannot be solved using BFS since graph is weighted and weights >= 0
// For unweighted graph, we should use BFS for finding the shortest path
 
 
#include <bits/stdc++.h>
using namespace std;
 
#define ll long long int
#define ff first
#define ss second
#define INF numeric_limits<ll>::max()
 
 
int main() {
	ll n, m;
	cin >> n >> m;
	vector<vector<ll>> G(n + 1);
	ll u, v, c;
	map<pair<ll, ll>, ll> mp; 
	for(ll i = 0; i < m; ++i){
		cin >> u >> v >> c;
		G[u].push_back(v);
		if(mp.find({u, v}) == mp.end()){
			mp[{u, v}] = c;
		}
		else{
			mp[{u, v}] = min(c, mp[{u, v}]);
		}
	}
	priority_queue<pair<ll, ll>> pq;
	pq.push({0, 1});
	vector<ll> sh_pth(n + 1, INF);
	vector<bool> vis(n, 0);
	while(pq.size()){	
		pair<ll, ll> tp = pq.top();
		pq.pop();
		ll nd = tp.ss;
		if(vis[nd]){
			continue;
		}
		vis[nd] = 1;
		ll d = abs(tp.ff);
		sh_pth[nd] = min(d, sh_pth[nd]);
		for(auto it : G[nd]){
			if(d + mp[{nd, it}] < sh_pth[it]){
				pq.push({-(d + mp[{nd, it}]), it});
				sh_pth[it] = d + mp[{nd, it}];
			}
		}
	}
	for(ll i =  1; i <= n; ++i) {
		cout << sh_pth[i] << " ";
	}
	cout << endl;
	return 0;
}
