#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ff first
#define ss second


bool is_valid(ll x, ll y, ll n, ll m, vector<string> &strs) {
	return (x >= 0 && x < n && y >= 0 && y < m && strs[x][y] == '.');
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	ll n, m;
	cin >> n >> m;
	vector<string> strs(n);
	ll ax, ay; // position of 'A'
	vector<vector<ll>> monster_sh_pth(n, vector<ll>(m, n * m + 1));
	queue<pair<pair<ll, ll>, ll>> Qm;
	for(ll i = 0; i < n; ++i) {
		cin >> strs[i];
		for(ll j = 0; j < (ll)strs[i].size(); ++j) {
			if(strs[i][j] == 'M'){
				Qm.push({{i, j}, 0}); // Push Monster position to queue for finding shortest path to other cell
				monster_sh_pth[i][j] = 0;
			}
			else if(strs[i][j] == 'A') {
				ax = i;
				ay = j;
			}
		}
	}
	vector<vector<bool>> vis_m(n, vector<bool>(m, 0));
	while(Qm.size()){
		pair<pair<ll, ll>, ll> fr = Qm.front();
		Qm.pop();
		ll x = fr.ff.ff;
		ll y = fr.ff.ss;
		ll d = fr.ss;
		vis_m[x][y] = 1;
		if(is_valid(x + 1, y, n, m, strs) && !vis_m[x + 1][y]) {
			Qm.push({{x + 1, y}, d + 1});
			monster_sh_pth[x + 1][y] = d + 1;
			vis_m[x + 1][y] =  1;
		}
		if(is_valid(x - 1, y, n, m, strs) && !vis_m[x - 1][y]) {
			Qm.push({{x - 1, y}, d + 1});
			monster_sh_pth[x - 1][y] = d + 1;
			vis_m[x - 1][y] = 1;
		}
		if(is_valid(x, y + 1, n, m, strs) && !vis_m[x][y + 1]) {
			Qm.push({{x, y + 1}, d + 1});
			monster_sh_pth[x][y + 1] = d + 1;
			vis_m[x][y + 1] = 1;
		}
		if(is_valid(x, y - 1, n, m, strs) && !vis_m[x][y - 1]) {
			Qm.push({{x, y - 1}, d + 1});
			monster_sh_pth[x][y - 1] = d + 1;
			vis_m[x][y - 1] = 1;
		}
	}
	queue<pair<pair<ll, ll>, ll>> q;
	q.push({{ax, ay}, 0});
	vector<vector<char>> steps(n, vector<char>(m, 'X'));
	ll x, y, d;
	bool poss = false;
	vector<vector<bool>> vis(n, vector<bool>(m, 0));
	while(q.size()) {
		pair<pair<ll, ll>, ll> c = q.front();
		q.pop();
		x = c.ff.ff;
		y = c.ff.ss;
		d = c.ss;
		vis[x][y] = 1;
		if(d >= monster_sh_pth[x][y]){
			continue;
		}
		if(x == n - 1 || x == 0 || y == m - 1 || y == 0){
			poss = true;
			break;
		}
		if(is_valid(x + 1, y, n, m, strs) && !vis[x + 1][y]){
			vis[x + 1][y] = 1;
			q.push({{x + 1, y}, d + 1});
			steps[x + 1][y] = 'U';
		}
		if(is_valid(x - 1, y, n, m, strs) && !vis[x - 1][y]){
			vis[x - 1][y] = 1;
			q.push({{x - 1, y}, d + 1});
			steps[x - 1][y] = 'D';
		}
		if(is_valid(x, y + 1, n, m, strs) && !vis[x][y + 1]){
			vis[x][y + 1] = 1;
			q.push({{x, y + 1}, d + 1});
			steps[x][y + 1] = 'L';
		}
		if(is_valid(x, y - 1, n, m, strs) && !vis[x][y - 1]){
			vis[x][y - 1] = 1;
			q.push({{x, y - 1}, d + 1});
			steps[x][y - 1] = 'R';
		}
	}
	if(poss) {
		string ans = "";
		while(steps[x][y] != 'X') {
			if(steps[x][y] == 'L'){
				ans += 'R';
				y--;
			}
			else if(steps[x][y] == 'R'){
				ans += 'L';
				y++;
			}
			else if(steps[x][y] == 'U'){
				ans += 'D';
				x--;
			}
			else{
				ans += 'U';
				x++;
			}
		}
		cout << "YES\n";
		cout << ans.size() << endl;
		reverse(ans.begin(), ans.end());
		cout << ans << endl;
	}
	else{
		cout << "NO\n";
	}
	return 0;
}