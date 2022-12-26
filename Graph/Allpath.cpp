#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

class Graph
{
private:
	int V;
	vector<int> E[100];
public:
	Graph(int V) : V(V) {}
	void addEdge(int u, int v)	{E[u].push_back(v);}
	
	bool isExist(int S, vector<int> path)
	{
		for (int x : path) if (x == S) return 1;
		return 0;
	}

	void DFS(int S, int T, vector<int> path, int &cnt)
	{
		//can use array counting 
		if (isExist(S, path)) return;

		if (S == T) {
			cnt++;
			for (int x : path) cout << x << "->";
			return cout << T << endl, void();
		}
		
		path.push_back(S);
		for (int x: E[S]) DFS(x, T, path, cnt);
		path.pop_back();
	}
};

int main()
{
	Graph g(10);
	vector<int> path;
	int cnt = 0;
	
	//init
	g.addEdge(1, 2);	g.addEdge(1, 4);
	g.addEdge(2, 4);	g.addEdge(2, 3);
	g.addEdge(3, 4);	g.addEdge(3, 5);
	g.addEdge(4, 5);	g.addEdge(2, 1);
	g.addEdge(1, 3);    g.addEdge(5, 6);
	g.addEdge(4, 1);
	
	//input u v
	int u, v;
	cout << "From ... to ... : ";
	cin >> u >> v;
	
	//find path and count
	g.DFS(u, v, path, cnt);
	
	//print
	cout << "The number of paths from " << u << " to " << v << ": " << cnt << " paths\n";
	
	return 0;
}
