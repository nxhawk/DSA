#include<iostream>

using namespace std;

int ternarySearch(int A[], int l, int r, int val)
{
	if (l > r) return -1;
	
	int mid1 = l + (r - l) / 3, mid2 = r - (r - l) / 3;
	if (A[mid1] == val) return mid1;
	if (A[mid2] == val) return mid2;

	if (val < A[mid1]) return ternarySearch(A, l, mid1 - 1, val);
	if (A[mid1] < val && val < A[mid2]) return ternarySearch(A, mid1 + 1, mid2 - 1, val);
	return ternarySearch(A, mid2 + 1, r, val);
}

int main() 
{
	int a[] = {1, 3, 4, 8, 9, 10, 12, 15, 17, 20, 22, 24, 29};
	int n = sizeof(a) / sizeof(n);
	int val;
	cout << "Input val: ";
	cin >> val;
	cout << "Index: " << ternarySearch(a, 0, n - 1, val) << endl;
	return 0;
}