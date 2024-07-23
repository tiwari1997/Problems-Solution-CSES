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
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, x;
	cin >> n >> x;
	vector<int> p(n);
	for(int i = 0; i < n; ++i){
		cin >> p[i];
	}
	sort(p.begin(), p.end());
	int lp = 0;
	int rp = n - 1;
	int ans = 0;
	while(lp <= rp){
		if(p[lp] + p[rp] <= x){
			ans++;
			lp++;
			rp--;
		}
		else{
			ans++;
			rp--;
		}
	}
	cout << ans << endl;
	return 0;
}
