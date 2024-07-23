// Solved this problem using Graph Coloring
// Color current node with 0 and it's  neighbouring nodes with 1
// Apply BFS for Graph Coloring

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ff first
#define ss second

int main() {
	ll n, m;
	cin >> n >> m;
	vector<vector<ll>> G(n);
	for(ll i = 0; i < m; ++i) {
		ll u, v;
		cin >> u >> v;
		u--; v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	vector<bool> vis(n, 0);
	vector<ll> color(n, -1);
	for(ll i = 0; i < n; ++i){
		if(!vis[i]){
			queue<ll> Q;
			Q.push(i);
			color[i] = 0;
			while(Q.size()){
				ll fr = Q.front();
				Q.pop();
				ll c = color[fr];
				for(auto it : G[fr]){
					if(color[it] != -1 && color[it] == c){
						cout << "IMPOSSIBLE\n";
						return 0;
					}
					else if(color[it] == -1){
						color[it] = c ^ 1;
						vis[it] = 1;
						Q.push(it);
					}
				}
			}
		}
	}
	for(ll i = 0; i < n; ++i){
		cout << color[i] + 1 << " ";
	}
	cout << endl;
	return 0;
}