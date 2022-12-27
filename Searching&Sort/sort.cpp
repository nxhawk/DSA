#include<iostream>
#include<fstream>//read file
#include<string>//using string
#include<time.h>//tick time

using namespace std;

int* data1;//array data for Bubble Sort
int* data2;//array data for Selection Sort 
int* data3;//array data for Heap Sort
int* data4;//array data for Quick Sort
int* data5;//array data for Merge Sort

//read data from file input (filename, len)
void readInputFile(string filename, int lenFile)
{
	ifstream f;
	f.open(filename, ios_base::in);
	if (!f.is_open()) {
		cout << "Failed open file\n";
		return;
	}

	data1 = new int[lenFile];
	data2 = new int[lenFile];
	data3 = new int[lenFile];
	data4 = new int[lenFile];
	data5 = new int[lenFile];//set length array

	//read data from file
	for (int i = 0; i < lenFile; i++)
	{
		f >> data1[i];
		data2[i] = data3[i] = data4[i] = data5[i] = data1[i];//copy data
	} 
	
	f.close();
}

//Swap two element
void swapItem(int& arr1, int& arr2)
{
	int tmp = arr1;
	arr1 = arr2;
	arr2 = tmp;
}

/*-----------------------------------Bubble Sort-------------------------------------*/
void bubbleSort(int* arr, int len)
{
	for (int i = 1; i < len - 1; i++)
		for (int j = len - 1; j > i; j--)// chay tu cuoi len nhu noi bot
			if (arr[j - 1] > arr[j]) // dieu kien sap xep tang dan 
				swapItem(arr[j - 1], arr[j]);
	//for (int i = 0; i < len; i++) cout << arr[i] << " ";
}
/*---------------------------------End Bubble Sort-----------------------------------*/


/*----------------------------------Selection Sort-----------------------------------*/
void selectionSort(int* arr, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < len; j++)// tim vi tri gia tri nho nhat trong khoang sau
			if (arr [j] < arr [minIndex])
				minIndex = j;
		swapItem(arr[i], arr[minIndex]);
	}
	//for (int i = 0; i < len; i++) cout << arr[i] << " ";
}
/*--------------------------------End Selection Sort---------------------------------*/


/*------------------------------------Heap Sort--------------------------------------*/
//heapify recursive
void heapify(int* arr, int len, int i) {
	int max = i, l = i * 2 + 1, r = i * 2 + 2;// khoi tao vt max, nut trai va nut phai cua node hien tai dang kiem tra
	if (l < len && arr[l] > arr[max]) max = l;// tim vi tri max
	if (r < len && arr[r] > arr[max]) max = r;// tim vi tri max
	if (max != i) {
		swapItem(arr[i], arr[max]);// doi cho phan tu lon nhat
		heapify(arr, len, max);// vun lai dong phia duoi
	}
}

void heapSort(int* arr, int len) {
	for (int i = len / 2 - 1; i >= 0; i--)
		heapify(arr, len, i);// vun lai tung dinh

	for (int i = len - 1; i > 0; i--) {// loai bo lan luot cac phan tu cuoi ra khoi heap
		swapItem(arr[0], arr[i]);// doi vi tri phan tu max ve cuoi
		heapify(arr, i, 0);// vun lai dong 
	}
	//for (int i = 0; i < len; i++) cout << arr[i] << " ";
}
/*----------------------------------End Heap Sort------------------------------------*/


/*-----------------------------------Quick Sort--------------------------------------*/
int partition(int* arr, int l, int r) {
	int i = l - 1, j = r, v = arr[r];
	for (;;) {
		while (arr[++i] < v);
		while (v < arr[--j]) if (j == l) break;
		if (i >= j) break;
		swapItem(arr[i], arr[j]);
	}
	swapItem(arr[i], arr[r]);
	return i;
}

void quickSort(int* arr, int l, int r) {
	if (r <= l) return;
	int i = partition(arr, l, r);
	quickSort(arr, l, i - 1);
	quickSort(arr, i + 1, r);
}
/*---------------------------------End Quick Sort------------------------------------*/


/*-----------------------------------Merge Sort--------------------------------------*/
void merge(int* arr, int left, int middle, int right)
{
	int leftSize = middle - left + 1;
	int	rightSize = right - middle;

	int* L = new int[leftSize];
	int* R = new int[rightSize];

	for (int i = 0; i < leftSize; i++) L[i] = arr[i + left];
	for (int i = 0; i < rightSize; i++) R[i] = arr[i + middle + 1];

	int i = 0, j = 0, k = left;
	while (i < leftSize && j < rightSize)
		arr[k++] = (L[i] < R[j]) ? L[i++] : R[j++];

	while (i < leftSize)
		arr[k++] = L[i++];
	while (j < rightSize)
		arr[k++] = R[j++];

	delete[] L;
	delete[] R;
}

void mergeSort(int* arr, int left, int right) {
	if (left < right) {
		int middle = (left + right) / 2;
		mergeSort(arr, left, middle);
		mergeSort(arr, middle + 1, right);
		merge(arr, left, middle, right);
	}	
}
/*---------------------------------End Merge Sort------------------------------------*/

//clear array
void clearArr()
{
	delete[] data1;
	delete[] data2;
	delete[] data3;
	delete[] data4;
	delete[] data5;
}

//run main
void startAllSort(string filename, int len)
{
	clock_t start, end;
	readInputFile(filename, len);//read
	//SORT
	cout << "With file \"" << filename << "\":\n";
	start = clock();
	bubbleSort(data1, len);
	end = clock();
	cout <<" + Bubble Sort takes " << double(end - start) / CLOCKS_PER_SEC << "s\n";

	start = clock();
	selectionSort(data2, len);
	end = clock();
	cout << " + Selection Sort takes " << double(end - start) / CLOCKS_PER_SEC << "s\n";

	start = clock();
	heapSort(data3, len);
	end = clock();
	cout << " + Heap Sort takes " << double(end - start) / CLOCKS_PER_SEC << "s\n";

	start = clock();
	quickSort(data4, 0, len - 1);
	end = clock();
	cout << " + Quick Sort takes " << double(end - start) / CLOCKS_PER_SEC << "s\n";

	start = clock();
	mergeSort(data5, 0, len - 1);
	end = clock();
	cout << " + Merge Sort takes " << double(end - start) / CLOCKS_PER_SEC << "s\n";

	cout << "----------------------------------\n\n";
	clearArr();
}

int main()
{
	startAllSort("array_1000.csv", 1000);
	startAllSort("array_10000.csv", 10000);
	startAllSort("array_100000.csv", 100000);
	startAllSort("array_1000000.csv", 1000000);
	return 0;
}
