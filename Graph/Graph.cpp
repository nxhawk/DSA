//{}[]
#include<iostream>
#include<queue>
#include<math.h>
#include<vector>

using namespace std;

typedef pair<int, int> ii;

const int sz = int(1e4 + 5);


int n, m;
vector<ii> g[sz];
bool visit[sz];

bool check(int mid)
{
	memset(visit, false, sz);
	queue<int> q;

	visit[1] = true;
	q.push(1);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();

		for (ii e : g[u]) {
			int v = e.first, uv = e.second;

			if (uv <= mid && !visit[v])
			{
				visit[v] = true;
				q.push(v);
			}
		}
	} 
	return visit[n];
}

int main()
{
	cin >> n >> m;
	while(m--)
	{
		int u, v, w;
		cin >> u >> v >> w;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	} 

	int l = 1, r = 1e9, res = 0;

	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (check(mid)) res = mid, r = mid - 1;
		else l = mid + 1;
	} 
	cout << res;
	return 0;
}