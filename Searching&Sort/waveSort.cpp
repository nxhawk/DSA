#include<iostream>
#include<algorithm>
#include<math.h>

using namespace std;

void waveSort(int A[], int n)
{
	for (int i = 0; i < n; i+= 2)
	{
		if (i > 0 && A[i - 1] > A[i]) swap(A[i - 1], A[i]);
		if (i < n - 1 && A[i] < A[i + 1]) swap(A[i], A[i + 1]);
	} 
}

int main()
{
	int a[] = {1, 5, 23, 4, 23, 5, 6, 7, 4, 3, 12, 24, 76};
	int n = sizeof(a) / sizeof(int);
	waveSort(a, n);
	for (int x : a) cout << x << " ";
	return 0;
}
