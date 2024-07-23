#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define ff first
#define ss second
#define INF numeric_limits<ll>::max()

int main() {
	ll n, m, q;
	cin >> n >> m >> q;
	vector<vector<ll>> G(n + 1);
	map<pair<ll, ll>, ll> wt; 
	for(ll i = 0; i < m; ++i) { 
		ll u, v, w;
		cin >> u >> v >> w;
		G[u].push_back(v);
		G[v].push_back(u);
		ll x, y;
		x = min(u, v);
		y = max(u, v);
		if(wt.find({x, y}) != wt.end()) {
			wt[{x, y}] = min(w, wt[{x, y}]);
		}
		else{
			wt[{x, y}] = w;
		}
	}
	vector<vector<ll>> sh_pth(n + 1, vector<ll>(n + 1, INF));
	for(ll i = 1; i <= n; ++i){
		for(ll j = 1; j <= n; ++j){
			if(i == j){
				sh_pth[i][j] = 0;
			}
			else{
				ll x, y;
				x = min(i, j);
				y = max(i, j);
				if(wt.find({x, y}) != wt.end()){
					sh_pth[i][j] = wt[{x, y}];
				}
			}
		}
	}
	for(ll i = 1; i <= n; ++i){
		for(ll j = 1; j <= n; ++j){
			for(ll k = 1; k <= n; k++){
				if(sh_pth[j][i] + sh_pth[i][k] < sh_pth[j][k] && sh_pth[j][i] != INF && sh_pth[i][k] != INF){
					sh_pth[j][k] = sh_pth[j][i] + sh_pth[i][k]; 
				}
			}
		}
	}
	while(q--){
		ll u, v;
		cin >> u >> v;
		if(sh_pth[u][v] == INF){
			cout << -1 << endl;
		}
		else{
			cout << sh_pth[u][v] << endl;
		}
	}
	return 0;
}