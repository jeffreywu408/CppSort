#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

template<typename T>
void fillArray(T* a, int size, int max) {
    for (int i = 0; i < size; ++i) {
        double f = (double) rand() / RAND_MAX;
        a[i] = (T) (f * max);
    }
}

template<typename T>
void display(T* a, int n) {
    cout << "[";

    for (int i = 0; i < n - 1; i++) {
        cout << a[i] << ", ";
    }

    cout << a[n - 1] << "]" << endl;
}

template<typename T>
bool isSorted(T* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            return false;
        }
    }
    return true;
}

template<typename T>
void bubbleSort(T* a, int n) {
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 1; j <= i; j++) {
            if (a[j - 1] > a[j]) {
                swap(a[j], a[j - 1]);
            }
        }
    }
}

template<typename T>
void selectionSort(T* a, int n) {
    int min; //index of minimum
    for (int i = 0; i < n; i++) {
        //Linear search for the minimum
        min = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }

        //Put minimum into correct place
        if (min != i) {
            swap(a[i], a[min]);
        }
    }
}

template<typename T>
void insertionSort(T* a, int n) {
    for (int i = 1; i < n; i++) {
        //Take an unsorted element and insert it into correct sorted spot
        for (int j = i; j > 0 && a[j] < a[j - 1]; j--) {
            swap(a[j], a[j - 1]);
        }
    }
}

template<typename T>
void siftDown(T* a, int root, int end) {
    //Continually swap the root with the greatest child
    //until theres's no more children or the root is greater than the children
    while (2 * root + 1 <= end) {
        int sw = root; //index of the root element
        int child = 2 * root + 1; //index of the left child

        //Check left child
        if (a[child] > a[sw]) {
            sw = child;
        }

        //Check right child
        if ((child + 1 <= end) && (a[child + 1] > a[sw])) {
            sw = child + 1;
        }

        //Swap root with greatest child
        if (sw == root) {
            return;
        } else {
            swap(a[root], a[sw]);
            root = sw;
        }
    }
}

template<typename T>
void heapify(T* a, int n) {
    //Root Node is at index 0
    //Nth Node is at index (n + 1)
    //Left Child is at index (2n + 1)
    //Right Child is at index (2n + 2)
    for (int node = (n - 2) / 2; node >= 0; node--) {
        siftDown(a, node, n - 1);
    }
}

template<typename T>
void heapSort(T* a, int n) {
    heapify(a, n);

    //The array from [0, ... , i] is the heap
    //The array from [i+1, ... , end] is in sorted order
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        siftDown(a, 0, i - 1);
    }
}

template<typename T>
void merge(T* a, int left, int mid, int right) {
    int i, j, k;
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;

    //Temporary arrays
    T *L = new T[sizeLeft];
    T *R = new T[sizeRight];

    for (i = 0; i < sizeLeft; i++) {
        L[i] = a[left + i];
    }

    for (j = 0; j < sizeRight; j++) {
        R[j] = a[mid + j + 1];
    }

    //Merge the temporary arrays back into v[left, ..., right]
    i = 0; //Initial index of first sub-array
    j = 0; //Initial index of second sub-array
    k = left; //Initial index of merged sub-array
    while (i < sizeLeft && j < sizeRight) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }

        k++;
    }

    //Copy the remaining elements of left sub-array
    while (i < sizeLeft) {
        a[k] = L[i];
        i++;
        k++;
    }

    //Copy the remaining elements of right sub-array
    while (j < sizeRight) {
        a[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

template<typename T>
void mergeSort(T* a, int left, int right) {
    if (left < right) {
        //Same as (left + right)/2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

template<typename T>
void mergeSort(T* a, int n) {
    mergeSort(a, 0, n - 1);
}

template<typename T>
int partition(T* a, int first, int last) {
    //Randomly pick a pivot between lower index and higher index
    int pivotIndex = rand() % (last - first) + first;

    //Place pivot at the end of the sub-array
    swap(a[pivotIndex], a[last]);

    pivotIndex = last;
    T pivot = a[pivotIndex];

    //Partitioning
    int i = first;
    for (int j = first; j < last; j++) {
        if (a[j] <= pivot) {
            swap(a[i], a[j]);
            i++;
        }
    }

    //Move the pivot into position i
    swap(a[i], a[pivotIndex]);
    return i;
}

template<typename T>
void quickSort(T* a, int first, int last) {
    int pivotIndex;

    if (first < last) {
        pivotIndex = partition(a, first, last);
        quickSort(a, first, pivotIndex - 1);
        quickSort(a, pivotIndex + 1, last);
    }
}

template<typename T>
void quickSort(T* a, int n) {
    quickSort(a, 0, n - 1);
}

template<typename T>
void quickSort3(T* a, int first, int last) {
    //Quick Sort with a 3-Way Partition: [ < Pivot | = Pivot | > Pivot ]
    if (first < last) {
        //Randomly pick a pivot between lower index and higher index
        int pivotIndex = rand() % (last - first) + first;

        //Place pivot at the start of the sub-array
        swap(a[first], a[pivotIndex]);

        pivotIndex = first;
        T pivot = a[pivotIndex];

        //The upper index of the "less than pivot" partition
        int lt = first;
        //The lower index of the "greater than pivot" partition
        int gt = last;

        //Partitioning
        int i = first;
        while (i <= gt) {
            if (a[i] < pivot) {
                swap(a[lt], a[i]);
                i++;
                lt++;
            } else if (a[i] > pivot) {
                swap(a[gt], a[i]);
                gt--;
            } else {
                i++;
            }
        }

        //Recursively call on the left and right partitions
        quickSort3(a, first, lt - 1);
        quickSort3(a, gt + 1, last);
    }
}

template<typename T>
void quickSort3(T* a, int n) {
    quickSort3(a, 0, n - 1);
}

int main() {
    clock_t begin, end;
    int n;
    int max;

    cout << "Size of Array: ";
    cin >> n;
    if (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        n = 1000;
        cout << "Using Array Size = " << n << endl;
    }

    cout << "Max Value: ";
    cin >> max;
    if (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        max = 1000;
        cout << "Using Max Value = " << max << endl;
    }

    int array[n];

    fillArray(array, n, max);
    cout << endl << "Bubble Sort " << endl;
    //display(array, n);
    begin = clock();
    bubbleSort(array, n);
    end = clock();
    cout << "Sorted: ";
    (isSorted(array, n)) ? cout << "True" << endl : cout << "False" << endl;
    //display(array, n);
    cout << "Time: " << (double) (end - begin) / CLOCKS_PER_SEC << endl;

    fillArray(array, n, max);
    cout << endl << "Selection Sort" << endl;
    //display(array, n);
    begin = clock();
    selectionSort(array, n);
    end = clock();
    cout << "Sorted: ";
    (isSorted(array, n)) ? cout << "True" << endl : cout << "False" << endl;
    //display(array, n);
    cout << "Time: " << (double) (end - begin) / CLOCKS_PER_SEC << endl;

    fillArray(array, n, max);
    cout << endl << "Insertion Sort" << endl;
    //display(array, n);
    begin = clock();
    insertionSort(array, n);
    end = clock();
    cout << "Sorted: ";
    (isSorted(array, n)) ? cout << "True" << endl : cout << "False" << endl;
    //display(array, n);
    cout << "Time: " << (double) (end - begin) / CLOCKS_PER_SEC << endl;

    fillArray(array, n, max);
    cout << endl << "Heap Sort" << endl;
    //display(array, n);
    begin = clock();
    heapSort(array, n);
    end = clock();
    cout << "Sorted: ";
    (isSorted(array, n)) ? cout << "True" << endl : cout << "False" << endl;
    //display(array, n);
    cout << "Time: " << (double) (end - begin) / CLOCKS_PER_SEC << endl;

    fillArray(array, n, max);
    cout << endl << "Merge Sort" << endl;
    //display(array, n);
    begin = clock();
    mergeSort(array, n);
    end = clock();
    cout << "Sorted: ";
    (isSorted(array, n)) ? cout << "True" << endl : cout << "False" << endl;
    //display(array, n);
    cout << "Time: " << (double) (end - begin) / CLOCKS_PER_SEC << endl;

    fillArray(array, n, max);
    cout << endl << "Quick Sort" << endl;
    //display(array, n);
    begin = clock();
    quickSort(array, n);
    end = clock();
    cout << "Sorted: ";
    (isSorted(array, n)) ? cout << "True" << endl : cout << "False" << endl;
    //display(array, n);
    cout << "Time: " << (double) (end - begin) / CLOCKS_PER_SEC << endl;

    fillArray(array, n, max);
    cout << endl << "Quick Sort (3-Way Partition)" << endl;
    //display(array, n);
    begin = clock();
    quickSort3(array, n);
    end = clock();
    cout << "Sorted: ";
    (isSorted(array, n)) ? cout << "True" << endl : cout << "False" << endl;
    //display(array, n);
    cout << "Time: " << (double) (end - begin) / CLOCKS_PER_SEC << endl;

    fillArray(array, n, max);
    cout << endl << "std:sort" << endl;
    //display(array, n);
    begin = clock();
    sort(array, array + n);
    end = clock();
    cout << "Sorted: ";
    (isSorted(array, n)) ? cout << "True" << endl : cout << "False" << endl;
    //display(array, n);
    cout << "Time: " << (double) (end - begin) / CLOCKS_PER_SEC << endl;

    return 0;
}
