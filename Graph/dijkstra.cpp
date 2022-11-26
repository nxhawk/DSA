//{}[]

#include<vector>
#include<iostream>
#include<math.h>
#include<cstring>
#include<fstream>

using namespace std;

const int sz = 1000;
const int oo = 1e9;

int n, s, t;
int a[sz][sz], front[sz + 7], d[sz + 7];
bool ok[sz + 7];

void input()
{
	ifstream f;
	f.open("data.txt", ios_base::in | ios_base::binary);
	f >> n >> s >> t;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			f >> a[i][j];
			if (a[i][j] == 0) a[i][j] = oo;
		}
	f.close();
}

void dijkstra(int S, int F)
{
	//init
	for (int v = 1; v <= n; v++)
	{
		d[v] = a[S][v];
		front[v] = S;
		ok[v] = false;
	} 
	//visit S first 
	front[S] = 0;
	d[S] = 0;
	ok[S] = true;
	//find path min to F
	int stop = 0;
	while(!ok[F] && stop <= n)
	{
		stop++;
		//find mind D
		int minp = oo, u = -1;
		for (int v = 1; v <= n; v++)
			if (!ok[v] && minp > d[v]) {
				minp = d[v];
				u = v;
			}
		//tick ok
		ok[u] = true;
		//update d for  
		if (!ok[F]) {
			for (int v = 1; v <= n; v++) 
				if (!ok[v] && d[v] > d[u] + a[u][v]) {
					d[v] = d[u] + a[u][v];
					front[v] = u; // save front edge
				}
		}
	} 
}

void trace(int F)
{
	if (front[F] == 0) return;
	trace(front[F]);
	cout << F << "->";
}

void output(int S, int F)
{
	if (!ok[F]) cout << "Khong co duong di tu " << S << " den " << F << "\n";
	cout << "Duong di ngan nhat tu " << S << " den " << F << "la: \n";
	cout << S << "->";
	trace(F);
	cout << "endl\n";
	cout << "Do dai duong di: " << d[F] << endl;
}

int main()
{
	input();
	dijkstra(s, t);
	output(s, t);
	return 0;
}