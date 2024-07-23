// Find all Cycles in an undirected graph using graph coloring
// Link: https://www.geeksforgeeks.org/print-all-the-cycles-in-an-undirected-graph/

#include <bits/stdc++.h>
using namespace std;

#define ll int
#define ff first
#define ss second

void find_cycle(vector<vector<ll>> &G, ll curr_node, ll parent_node, vector<ll> &color, vector<ll> &ans, vector<ll> &parent) {
	if(color[curr_node] == 2 || ans.size()) {
		return;
	}
	else if(color[curr_node] == 1) {
		// Cycle Detected
		ll cur = parent_node;
		while(cur != curr_node) {
			ans.push_back(cur);
			cur = parent[cur];
		}	
		ans.push_back(curr_node);
		ans.push_back(parent_node);
	}
	else {
		color[curr_node] = 1;
		parent[curr_node] = parent_node;
		for(auto nd : G[curr_node]) {
			if(nd == parent_node) {
				continue;
			}
			find_cycle(G, nd, curr_node, color, ans, parent);
		}
		color[curr_node] = 2;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	ll n, m;
	cin >> n >> m;
	vector<vector<ll>> G(n + 1);
	for(ll i = 0; i < m; ++i) {
		ll u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	vector<ll> color(n + 1, 3);
	vector<ll> parent(n + 1, -1);
	for(ll i = 1; i <= n; ++i) {
		if(color[i] == 3) {
			vector<ll> ans;
			find_cycle(G, i, -1, color, ans, parent);
			if(ans.size()) {
				cout << ans.size() << endl;
				for(auto it : ans) {
					cout << it << " ";
				}
				cout << endl;
				return 0;
			}
		}
	}
	cout << "IMPOSSIBLE\n";
	return 0;
}
