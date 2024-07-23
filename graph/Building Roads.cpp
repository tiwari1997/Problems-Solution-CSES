#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

void bfs(vector<vector<ll>> &G, vector<bool> &vis, ll src) {
	queue<ll> Q;
	Q.push(src);
	while(Q.size()){
		ll fr = Q.front();
		Q.pop();
		vis[fr] = 1;
		for(auto ele : G[fr]){
			if(!vis[ele]){
				vis[ele] = 1;
				Q.push(ele);
			}
		}
	}
}

vector<ll> count_components(vector<vector<ll>> &G){
	ll n = G.size();
	vector<bool> vis(n, 0);
	vector<ll> cmps;
	for(ll i = 0; i < n; ++i){
		if(!vis[i]){
			bfs(G, vis, i);
			cmps.push_back(i);
		}
	}
	return cmps;
}

int main() {
	ll n, m;
	cin >> n >> m;
	vector<vector<ll>> G(n);
	for(ll i = 0; i < m; ++i){
		ll u, v;
		cin >> u >> v;
		u--; v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	vector<ll> cmps = count_components(G);
	cout << cmps.size() - 1 << endl;
	for(ll i = 1; i < cmps.size(); ++i){
		cout << cmps[i - 1] + 1 << " " << cmps[i] + 1 << endl;
	}
	return 0;
}