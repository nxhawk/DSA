//{}[]

#include<iostream>
#include<vector>
#include<math.h>
#include<cstring>

using namespace std;

int hashFunc(int k, int m)
{
	return k % m;
}

//Do bac 2
int hashFunc2(int k, int i, int m)
{
	return (k + i * i) % m;
}

//dung cho bam kep
int h2(int k)
{
	return 5 - (k % 5);
}
//Bam kep voi h2(k) = 5 - (k mod 5)
int hasFuncDouble(int k1, int k2, int i, int m)
{
	return (k1 + k2 * i) % m;
}

void createHash2(vector<int>&a, int mod)
{
	a.assign(mod, -1);
	//
	int data[] = { 22, 86, 13, 79, 24, 35, 52, 42, 64, 47, 77 };
	int n = sizeof(data) / sizeof(int);

	for (int i = 0; i < n; i++)
	{
		int k1 = hashFunc(data[i], mod), k2 = h2(data[i]);
		if (a[k1] == -1) a[k1] = data[i];
		else {
			int tk = k1, k = 1;
			while(a[tk]!=-1) {
				tk = hasFuncDouble(k1, k2, k++, mod);
				if (tk == k1) break;
			}
			if (a[tk] == -1) a[tk] = data[i];
		}
	} 
}

void createHash(vector<int>&a, int mod)
{
	a.assign(mod, -1);
	int data[] = {22, 86, 13, 79, 24, 35, 52, 42, 64, 47, 77};
	int n = sizeof(data) / sizeof(int);
	
	for (int i = 0; i < n; i++)
	{
		int key = hashFunc(data[i], mod);
		if (a[key] == -1) a[key] = data[i];
		else {
			int tkey = key, k = 0;
			while(a[tkey]!=-1) {
				tkey = hashFunc2(key, ++k, mod);
				if (tkey == key) break;
			}
			if (a[tkey] == -1) a[tkey] = data[i];
		}
	}
}

void printHash(vector<int> a)
{
	for (int i = 0; i < a.size(); i++)
		cout << "Slot "<<i << ": " << a[i] << endl;
}

int main()
{
	vector<int> a;
	//Do bac 2
	createHash(a, 17);
	printHash(a);
	cout << endl;
	//Bam kep
	createHash2(a, 17);
	printHash(a);
	return 0;
}