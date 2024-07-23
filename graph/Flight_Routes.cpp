// Hint : https://usaco.guide/problems/cses-1196-flight-routes/solution

#include <bits/stdc++.h>
#include <thread>
using namespace std;

#define ll long long int
#define ff first
#define ss second
#define all(v) v.begin(), v.end()

// Required For Shortest Path in Graph
#define MAXLL numeric_limits<ll>::max()
#define MINLL numeric_limits<ll>::min()

// Required For Dijkstra Algorithm
#define max_heap priority_queue<ll>
#define min_heap priority_queue<ll, vector<ll>, greater<ll>>


int main() {
	ll n, m, k;
	cin >> n >> m >> k;
	vector<pair<ll, ll>> adj[n + 1];
	ll u, v, w, d;
	for(ll i = 0; i < m; ++i){
		cin >> u >> v >> w;
		adj[u].push_back({v, w});
	}
	// Maintain a priority queue of the k best distances found for each vertex
	max_heap pq_k[n + 1]; // array of priority queue(max heap)
	priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;//(min_heap)
	pq.push({0, 1});
	vector<bool> vis(n + 1, 0);
	while(pq.size()){
		pair<ll, ll> tp = pq.top();
		pq.pop();
		u = tp.ss;
		d = tp.ff;
		if(vis[u]){
			continue;
		}
		bool flag = false;
		for(auto it : adj[u]){
			ll x = it.ff;
			ll y = it.ss;
			if(pq_k[x].size() < k){
				pq_k[x].push(d + y);
				pq.push({d + y, x});
				flag = true;
			}
			else if(pq_k[x].size() == k && pq_k[x].top() > (d + y)){
				pq_k[x].pop();
				pq_k[x].push(d + y);
				pq.push({d + y, x});
				flag = true;
			}
		}
		if(!flag){
			vis[u] = 1;
		}
	}
	vector<ll> ans;
	while(pq_k[n].size()){
		ans.push_back(pq_k[n].top());
		pq_k[n].pop();
	}
	reverse(all(ans));
	for(auto ele : ans){
		cout << ele << " ";
	}
	cout << endl;
	return 0;
}
