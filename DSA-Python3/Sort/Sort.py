# init array
A = [1, 76, 21, 5, 12, 194, 2]


def selectionSort(A, l, r):
    #O(n^2), stable
    for i in range(l, r):
        min_idx = i
        for j in range(i+1, r+1):
            if (A[j] < A[min_idx]):
                min_idx = j

        A[i], A[min_idx] = A[min_idx], A[i]


def insertionSort(A, l, r):
    # O(n^2), stable
    for i in range(l, r + 1):
        saved = A[i]
        j = i - 1
        while j >= l and saved < A[j]:
            A[j + 1] = A[j]
            j -= 1
        A[j + 1] = saved


def bubbleSort(A, l, r):
    #O(n^2), stable
    for i in range(l + 1, r):
        for j in range(r, i, -1):
            if A[j - 1] > A[j]:
                A[j - 1], A[j] = A[j], A[j - 1]


def bubbleSort_recursive(A, l, r):
    if l >= r or r - 1 == l:
        return

    for i in range(l, r):
        if (A[i] > A[i + 1]):
            A[i], A[i + 1] = A[i + 1], A[i]

    bubbleSort_recursive(A, l, r - 1)


def shellSort(A, l, r):
    # O(n^2), no stable
    h = 1
    while h <= (r - l) // 3:
        h = 3*h + 1
    while h > 0:
        for i in range(l + h, r+1):
            j = i
            v = A[i]
            while j >= l + h and v < A[j - h]:
                A[j] = A[j - h]
                j -= h
            A[j] = v
        h //= 3


def heapify(A, N, i):
    curr = i
    l = 2*i+1
    r = 2*i+2

    if l < N and A[l] > A[curr]:
        curr = l
    if r < N and A[r] > A[curr]:
        curr = r

    if curr != i:
        A[i], A[curr] = A[curr], A[i]
        heapify(A, N, curr)


def heapSort(A, N):
    # O(nlogn), no stable
    for i in range(N//2 - 1, -1, -1):
        heapify(A, N, i)

    for i in range(N-1, 0, -1):
        A[0], A[i] = A[i], A[0]
        heapify(A, i, 0)


def merge(A, l, m, r):
    L = A[l:m+1]
    R = A[m+1:r+1]
    i = j = 0
    k = l
    while i < len(L) and j < len(R):
        if L[i] <= R[j]:
            A[k] = L[i]
            i += 1
        else:
            A[k] = R[j]
            j += 1
        k += 1

    while i < len(L):
        A[k] = L[i]
        k += 1
        i += 1

    while j < len(R):
        A[k] = R[j]
        k += 1
        j += 1


def mergeSort(A, l, r):
    # O(nlogn), stable
    if (r <= l):
        return
    m = (l + r) // 2
    mergeSort(A, l, m)
    mergeSort(A, m + 1, r)
    merge(A, l, m, r)


def partition(A, l, h):
    pivot = A[h]
    i = l
    j = h - 1
    while True:
        while A[i] < pivot:
            i += 1
        while pivot < A[j]:
            j -= 1
            if j == l:
                break
        if i >= j:
            break
        A[i], A[j] = A[j], A[i]

    A[i], A[h] = A[h], A[i]
    print("pivot =", i, ':', end=" ")
    for k in range(l, h + 1):
        print(A[k], end=" ")
    print()
    return i


def quickSort(A, l, h):
    # O(nlogn), no stable
    if l < h:
        p = partition(A, l, h)
        quickSort(A, l, p - 1)
        quickSort(A, p + 1, h)


def countingSort(A):
    #O(n + k), stable
    max_element = int(max(A))
    min_element = int(min(A))
    range_of_elements = max_element - min_element + 1

    count = [0 for _ in range(range_of_elements)]
    output = [0 for _ in range(len(A))]

    for i in range(len(A)):
        count[A[i] - min_element] += 1

    for i in range(1, len(count)):
        count[i] += count[i - 1]

    for i in range(len(A)-1, -1, -1):
        output[count[A[i] - min_element] - 1] = A[i]
        count[A[i]-min_element] -= 1

    return output


if __name__ == '__main__':
    #selectionSort(A, 0, len(A) - 1)
    #insertionSort(A, 0, len(A) - 1)
    #bubbleSort(A, 0, len(A) - 1)
    #bubbleSort_recursive(A, 0, len(A) - 1)
    #shellSort(A, 0, len(A) - 1)
    #heapSort(A, len(A))
    #mergeSort(A, 0, len(A) - 1)
    #quickSort(A, 0, len(A) - 1)
    #A = countingSort(A)

    # print result
    print("Sorted Array")
    for x in A:
        print("%d" % x, end=" ")
