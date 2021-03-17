#include <iostream>
#include <sys/select.h>
#include <vector>
#include <memory>
using namespace std;

//堆排序：堆调整
void adujust_heap(int arr[], int start, int end) {
    int dad = start;
    int son = 2 * dad + 1;

    while (son <= end) {
        if (son + 1 <= end && arr[son] < arr[son + 1]) ++son;

        if (arr[son] > arr[dad]) {
            swap(arr[son], arr[dad]);
            dad = son;
            son = 2 * dad + 1;
        } else break;
    }
}

//堆排序
void heap_sort(int arr[], int len) {
    for (int i = len / 2 - 1; i >= 0; --i) {
        adujust_heap(arr, i, len - 1);
    }
    for (int i = len - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        adujust_heap(arr, 0, i - 1);
    }
}


//快速排序
void quick_sort(int arr[], int left, int right) {
    if (right - left <= 1) return;
    int slow = left + 1;
    int quick = left + 1;
    while (quick < right) {
        if (arr[quick] < arr[left]) swap(arr[slow++], arr[quick]);
        ++quick;
    }
    swap(arr[left], arr[slow - 1]);
    quick_sort(arr, left, slow);
    quick_sort(arr, slow, right);
}

//归并排序
void merge_sort(int arr[], int left, int right) {
    if (right - left <= 1) return;
    int mid = (right - left) / 2 + left;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid, right);
    if (left == mid || mid == right) return;
    else {
        vector<int> tmp(&arr[left], &arr[mid]);
        int posA = 0;
        int n = tmp.size();
        int posB = mid;
        while (posA < n && posB < right) {
            if (tmp[posA] < arr[posB]) arr[left++] = tmp[posA++];
            else arr[left++] = arr[posB++];
        }
        while (posA < n) {
            arr[left++] = tmp[posA++];
        }
    }
}

//冒泡排序
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
        }
    }
}

//选择排序
void select_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int imin = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[imin]) imin = j;
        }
        swap(arr[i], arr[imin]);
    }
}

//插入排序
void insert_sort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; --j) {
            swap(arr[j], arr[j - 1]);
        }
    }
}
int main() {
    vector<int> vec = {5, 2, 3, 1, 2, 3, 4};
//    heap_sort(&vec[0], vec.size());
//    quick_sort(&vec[0], 0, vec.size());
//    merge_sort(&vec[0], 0, vec.size());
//    bubble_sort(&vec[0], vec.size());
//    select_sort(&vec[0], vec.size());
    insert_sort(&vec[0], vec.size());
    for (auto x : vec) cout << x << " ";
    cout << endl;
}
