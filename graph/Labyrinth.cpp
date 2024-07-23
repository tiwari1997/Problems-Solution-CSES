#include <bits/stdc++.h>
using namespace std;
 
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
 
#define ff first
#define ss second
#define MOD (int)(1e9 + 7)
#define all(v) v.begin(), v.end()
#define lcm(a, b) ((a * b) / __gcd(a, b))
 
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;

bool is_valid(ll x, ll y, ll n, ll m, vector<vector<bool>> &vis, vector<string> &strs){
	return (x >= 0 && x < n && y >= 0 && y < m && vis[x][y] == 0 && strs[x][y] != '#');
}

int main() {
	ll n, m;
	cin >> n >> m;
	vector<string> strs(n);
	ll a_x, a_y;
	for(ll i = 0; i < n; ++i){
		cin >> strs[i];
		for(ll j = 0; j < m; ++j){
			if(strs[i][j] == 'A'){
				a_x = i;
				a_y = j;
			}
		}
	}
	vector<vector<bool>> vis(n, vector<bool>(m, 0));
	vector<vector<char>> steps(n, vector<char>(m, 'X'));
	queue<pair<ll, ll>> Q;
	Q.push({a_x, a_y});
	ll x, y;
	while(Q.size()){
		pair<ll, ll> fr = Q.front();
		Q.pop();
		x = fr.ff;
		y = fr.ss;
		vis[x][y] = 1;
		if(strs[x][y] == 'B'){
			break;
		}
		if(is_valid(x + 1, y, n, m, vis, strs)){
			vis[x + 1][y] = 1;
			Q.push({x + 1, y});
			steps[x + 1][y] = 'U';
		}
		if(is_valid(x - 1, y, n, m, vis, strs)){
			vis[x - 1][y] = 1;
			Q.push({x - 1, y});
			steps[x - 1][y] = 'D';
		}
		if(is_valid(x, y + 1, n, m, vis, strs)){
			vis[x][y + 1] = 1;
			Q.push({x, y + 1});
			steps[x][y + 1] = 'L';
		}
		if(is_valid(x, y - 1, n, m, vis, strs)){
			vis[x][y - 1] = 1;
			Q.push({x, y - 1});
			steps[x][y - 1] = 'R';
		}
	}
	if(x < n && x >= 0 && y < m && y >= 0 && strs[x][y] == 'B'){
		cout << "YES\n";
		string ans = "";
		while(strs[x][y] != 'A'){
			if(steps[x][y] == 'D'){
				ans += 'U';
				x++;
			}
			else if(steps[x][y] == 'U'){
				ans += 'D';
				x--;
			}
			else if(steps[x][y] == 'L'){
				ans += 'R';
				y--;
			}
			else{
				ans += 'L';
				y++;
			}
		}
		reverse(ans.begin(), ans.end());
		cout << ans.size() << "\n" << ans << endl;
	}
	else{
		cout << "NO\n";
	}
	return 0;
}
