#include <bits/stdc++.h>
using namespace std;

#define ff first
#define ss second

typedef long long int ll;


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
	vector<ll> prev(n);
	vector<bool> vis(n, 0);
	queue<ll> Q;
	Q.push(0);
	while(Q.size()){
		ll fr = Q.front();
		Q.pop();
		vis[fr] = 1;
		for(auto it : G[fr]){
			if(!vis[it]){
				Q.push(it);
				prev[it] = fr;
				vis[it] = 1;
			}
		}
	}
	if(vis[n - 1]){
		vector<ll> ans;
		ans.push_back(n - 1);
		ll p = prev[n - 1];
		while(p != 0){
			ans.push_back(p);
			p = prev[p];
		}
		ans.push_back(0);
		reverse(ans.begin(), ans.end());
		cout << ans.size() << endl;
		for(auto it : ans){
			cout << it + 1 << " ";
		}
		cout << endl;
	}
	else{
		cout << "IMPOSSIBLE\n";
	}
	return 0;
}