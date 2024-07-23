#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define ff first
#define ss second

// Required For Shortest Path in Graph
#define MAXLL numeric_limits<ll>::max()
#define MINLL numeric_limits<ll>::min()
#define all(v) v.begin(), v.end()

// priority_queue<ll> pq --> Max Heap
// priority_queue<ll, vector<ll>, greater<ll>> ---> Min Heap

int main() {
	ll n, m;
	cin >> n >> m;
	vector<tuple<ll, ll, ll>> edges;
	vector<vector<ll>> G(n + 1);
	for(ll i = 0; i < m; ++i){
		ll u, v, w;
		cin >> u >> v >> w;
		tuple<ll, ll, ll> t = {u, v, w};
		edges.push_back(t);
		G[u].push_back(v);
	}
	vector<ll> comps;// number of components
	vector<bool> vis(n + 1, 0);
	for(ll i = 1; i <= n; ++i){
		if(!vis[i]){
			comps.push_back(i);
		}
		else{
			queue<ll> Q;
			Q.push(i);
			while(Q.size()){
				ll fr = Q.front();
				Q.pop();
				vis[fr] = 1;
				for(auto it : G[fr]){
					if(!vis[it]){
						vis[it] = 1;
						Q.push(it);
					}
				}
			}
		}
	}
	vector<ll> d(n + 1, MAXLL);
	vector<ll> p(n + 1, -1);
	for(auto ele : comps){
		d[ele] = 0;
	}
	ll x;
	for(ll i = 1; i <= n; ++i){
		x = -1;
		for(auto ed : edges){
			ll u, v, w;
			tie(u, v, w) = ed;
			if(d[u] != MAXLL && d[v] > d[u] + w){
				d[v] = d[u] + w;
				p[v] = u;
				x = v;
			}
		}
	}
	if(x == -1){
		cout << "NO\n";
	}
	else{
		cout << "YES\n";
		for (ll i = 1; i <= n; ++i){
            x = p[x];
		}

        vector<ll> cycle;
        for (ll v = x;; v = p[v]) {
            cycle.push_back(v);
            if (v == x && cycle.size() > 1)
                break;
        }
        reverse(cycle.begin(), cycle.end());
        for (ll v : cycle)
            cout << v << ' ';
        cout << endl;
	}
	return 0;
}
