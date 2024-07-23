#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define ff first
#define ss second

// Required For Shortest Path in Graph
#define MAXLL numeric_limits<ll>::max()
#define MINLL numeric_limits<ll>::min()

// priority_queue<ll> pq --> Max Heap
// priority_queue<ll, vector<ll>, greater<ll>> ---> Min Heap


int main() {
	ll n, m;
	cin >> n >> m;
	vector<vector<ll>> G1(n + 1);
	vector<vector<ll>> G2(n + 1);
	map<pair<ll, ll>, ll> wt;
	for(ll i = 0; i < m; ++i){
		ll u, v, w;
		cin >> u >> v >> w;
		G1[u].push_back(v);
		G2[v].push_back(u);
		if(wt.find({u, v}) != wt.end()){
			wt[{u, v}] = min(wt[{u, v}], w);
		}
		else{
			wt[{u, v}] = w;
		}
	}
	vector<ll> d1(n + 1, MAXLL);
	vector<bool> vis1(n + 1, 0);
	priority_queue<pair<ll, ll>> pq1;
	pq1.push({0, 1});
	d1[1] = 0;
	while(pq1.size()){
		pair<ll, ll> tp = pq1.top();
		pq1.pop();
		ll nd = tp.ss;
		ll ds = abs(tp.ff);
		if(vis1[nd]){
			continue;
		}
		vis1[nd] = 1;
		for(auto it : G1[nd]){
			if(d1[it] > ds + wt[{nd, it}]){
				d1[it] = ds + wt[{nd, it}];
				pq1.push({-d1[it], it});
			}
		}
	}
	vector<ll> d2(n + 1, MAXLL);
	vector<bool> vis2(n + 1, 0);
	priority_queue<pair<ll, ll>> pq2;
	pq2.push({0, n});
	d2[n] = 0;
	while(pq2.size()){
		pair<ll, ll> tp = pq2.top();
		pq2.pop();
		ll nd = tp.ss;
		ll ds = abs(tp.ff);
		if(vis2[nd]){
			continue;
		}
		vis2[nd] = 1;
		for(auto it : G2[nd]){
			if(d2[it] > ds + wt[{it, nd}]){
				d2[it] = ds + wt[{it, nd}];
				pq2.push({-d2[it], it});
			}
		}
	}
	ll ans = MAXLL;
	for(auto ed : wt){
		pair<ll, ll> p = ed.ff;
		ll u = p.ff;
		ll v = p.ss;
		if(d1[u] != MAXLL && d2[v] != MAXLL	){
			ans = min(ans, d1[u] + d2[v] + (ed.ss >> 1));
		}
	}
	cout << ans << endl;
	return 0;
}