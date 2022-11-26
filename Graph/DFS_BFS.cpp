//{}[]

#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<math.h>

using namespace std;

const int sz = 1e5 + 9;

vector<int> g[sz];
bool visit[sz];
vector<int> lt;
int n, m;

void DFS(int edge, int k)
{
	if (visit[edge]) return;
	visit[edge] = true;
	lt[edge] = k;
	for (int e : g[edge])
		DFS(e, k);
}

void findLT_DFS()
{
	int k = 0;
	memset(visit, false, n + 1);
	lt.assign(n + 1, 0);
	for (int i = 1; i <= n; i++)
		if (!visit[i]) {
			DFS(i, k);
			k++;
		}
	for (int i = 0; i < k; i++)
	{
		for (int e = 1; e <= n; e++)
			if (lt[e] == i) cout << e << " ";
		cout << endl;
	}
}

void BFS(int edge, int k)
{
	queue<int> q;
	q.push(edge);
	lt[edge] = k;
	visit[edge] = true;

	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		

		for (int v : g[u]) 
		if(!visit[v])
		{
			visit[v] = true;
			q.push(v);
			lt[v] = k;
		}
	} 
}

void findLT_BFS()
{
	memset(visit, false, n + 1);
	lt.assign(n + 1, 0);
	int k = 0;
	for (int i = 1; i <= n; i++)
		if (!visit[i]) {
			BFS(i, k);
			k++;
		}//
	for (int i = 0; i < k; i++)
	{
		for (int e = 1; e <= n; e++)
			if (lt[e] == i) cout << e << " ";
		cout << endl;
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	//tim thanh phan lien thong cua do thi bang hai cach
	findLT_DFS();
	findLT_BFS();
	return 0;
}