#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <functional>
using namespace std;

class MergeSort {
public:
    void Sort(vector<int>& array) {
        vector<int> temp(array.size());
        MergeSortRecursive(array, temp, 0, array.size() - 1);
    }

private:
    void MergeSortRecursive(vector<int>& array, vector<int>& temp, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            MergeSortRecursive(array, temp, left, mid);
            MergeSortRecursive(array, temp, mid + 1, right);
            Merge(array, temp, left, mid, right);
        }
    }

    void Merge(vector<int>& array, vector<int>& temp, int left, int mid, int right) {
        int i = left;
        int j = mid + 1;
        int k = left;

        while (i <= mid && j <= right) {
            if (array[i] <= array[j]) {
                temp[k++] = array[i++];
            }
            else {
                temp[k++] = array[j++];
            }
        }

        while (i <= mid) {
            temp[k++] = array[i++];
        }

        while (j <= right) {
            temp[k++] = array[j++];
        }

        for (int i = left; i <= right; ++i) {
            array[i] = temp[i];
        }
    }
};

int main() {
    setlocale(LC_ALL, "RUS");
    vector<int> numbers(10);

    cout << "Заполните массив 10 числами: ";
    for (int i = 0; i < 10; ++i) {
        cin >> numbers[i];
    }
    cout << endl;

    MergeSort mergeSort;

    auto sortFunction = [&mergeSort](vector<int>& arr) {
        mergeSort.Sort(arr);
        };

    thread mergeSortThread(sortFunction, ref(numbers));
    mergeSortThread.join();

    cout << "Отсортированный массив: ";
    for (const int& num : numbers) {
        cout << num << " ";
    }
}
