#include <bits/stdc++.h>
#include <thread> // Used for threading in c++
using namespace std;
 
#define ll long long int
#define ff first
#define ss second
#define all(v) v.begin(), v.end()
 
// Required For Shortest Path in Graph
#define MAXI INT_MAX
#define MINI INT_MIN
#define MOD (int)(1e9 + 7)
 
// Required For Dijkstra Algorithm
#define max_heap priority_queue<ll>
#define min_heap priority_queue<ll, vector<ll>, greater<ll>>

const int MAXN = 2e5 + 5; // Max Nodes in a Graph
const int MAXD = 30; // Max parent Depth 2 ^ 30 = 1e9
int parents[MAXN][MAXD];
vector<int> G[MAXN]; // UnWeighted Graph 
vector<pair<int, int>> GW[MAXN]; // Weighted Graph 
int color[MAXN]; // Used For Graph Coloring
bool vis[MAXN]; // Used For Graph Traversal
int parent[MAXN]; // Used for storing parent
vector<vector<int>> cycles; // used for storing all cycles
 
void find_all_cycles(int curr, int par, bool is_undirected){
	if(color[curr] == 2){
		return;
	}
	if(color[curr] == 1){
		ll cur = par;
		vector<int> v;
		v.push_back(cur);
		while(cur != curr){
			cur = parent[cur];
			v.push_back(cur);
		}
		cycles.push_back(v);
		return;
	}
	color[curr] = 1;
	parent[curr] = par;
	vis[curr] = 1;
	for(auto v : G[curr]){
		if(is_undirected && v == parent[curr]){
			continue;
		}
		find_all_cycles(v, curr, is_undirected);
	}
	color[curr] = 2;
}
 
void detect_and_find_all_cycles(int n, bool &is_undirected){
	for(int i = 1; i <= n; ++i){
		if(!vis[i]){
			find_all_cycles(i, -1, is_undirected);
		}
	}
}

void dfs(int src, int par){
	vis[src] = 1;
	for(auto adj : G[src]){
		if(par != adj && !vis[adj]){
			dfs(adj, src);
		}
	}
}

// Binary Jumping
// 15th parent of i = 8th parent of (4th parent of (2nd parent(1st parent of i)))
int jump(int a, int d) {
	for (int i = 0; i < MAXD; i++)
		if (d & (1 << i)) a = parents[a][i];
	return a;
}

int main() {
	int n;
	cin >> n;
	vector<int> out(n + 1);
	ll v;
	for(int i = 1; i <= n; ++i){
		cin >> v;
		out[i] = v;
	}
	vector<int> ans(n + 1, 0);
	vector<vector<int>> all_cmps;
	for(ll i = 1; i <= n; ++i){
		if(!vis[i]){
			int v = i;
			all_cmps.emplace_back();
			while(vis[v] == 0){
				all_cmps.back().push_back(v);
				vis[v] = 1;
				v = out[v];
			}
			all_cmps.back().push_back(v);
		}
	}
	for(int i = 0; i < (int)all_cmps.size(); ++i){
		int k = ans[all_cmps[i].back()];
		int pos = -1;
		for(int j = 0; j + 1 < (int)all_cmps[i].size(); ++j){
			if(all_cmps[i][j] == all_cmps[i].back()){
				k = 0;
				pos = j;
				break;
			}
		}
		if(pos != -1){
			int cyc_len = all_cmps[i].size() - 2 - pos + 1;
			for(int j = 0; j + 1 < (int)all_cmps[i].size(); ++j){
				if(j < pos){
					ans[all_cmps[i][j]] = cyc_len + pos - j;
				}
				else{
					ans[all_cmps[i][j]] = cyc_len;
				}
			}
		}
		else{
			for(int j = 0; j + 1 < (int)all_cmps[i].size(); ++j){
				ans[all_cmps[i][j]] = k + all_cmps[i].size() - 1 - j;
			}
		}

	}
	for(int j = 1; j <= n; ++j){
		cout << ans[j] << " ";
	}
	cout << endl;
	return 0;
}
