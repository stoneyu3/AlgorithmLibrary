#pragma once

#include <vector>

namespace sl {

/*
Contain algorithms for sorting.

Type T must overload:
1. operator <  for comparing.
2. operator << for running test. (not compulsory)
3. operator >> for running test. (not compulsory)

For usage, see function test().
*/
template <typename T>
class SortHelper {
public:
    /*
    Insertion sort.

    @param arr the array to sort
    */
    static void insertionSort(std::vector<T> &arr) {
        int n = arr.size();
        for (int i = 1; i < n; ++i) {
            if (arr[i] < arr[i - 1]) {
                T tmp = arr[i], j = i;
                while (j >= 1 && tmp < arr[j - 1]) {
                    arr[j] = arr[j - 1];
                    --j;
                }
                arr[j] = tmp;
            }
        }
    }

    /*
    Selection sort.

    @param arr the array to sort
    */
    static void selectionSort(std::vector<T> &arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; ++i) {
            int min = i;
            for (int k = i; k < n; ++k) {
                if (arr[k] < arr[min]) {
                    min = k;
                }
            }
            if (min != i) {
                swap(arr[i], arr[min]);
            }
        }
    }

    /*
    Shell sort.

    @param arr the array to sort
    */
    static void shellSort(std::vector<T> &arr) {
        int n = arr.size();
        for (int increment = n / 2; increment >= 1; increment /= 2) {
            for (int i = increment; i < n; ++i) {
                T tmp = arr[i];
                int j;
                for (j = i; j >= increment; j -= increment) {
                    if (tmp < arr[j - increment]) {
                        arr[j] = arr[j - increment];
                    } else {
                        break;
                    }
                }
                arr[j] = tmp;
            }
        }
    }

    /*
    Merge sort for array.

    @param arr the array to sort
    */
    static void mergeSort(std::vector<T> &arr) {
        std::vector<T> tmpArr(arr.size());
        mergeSortArray(arr, 0, arr.size() - 1, tmpArr);
    }

    /*
    List node declaration
    */
    struct ListNode {
        T val;
        ListNode* next;
    };

    /*
    Merge sort for list.

    @param h the head of the list to sort
    */
    static void mergeSort(ListNode *&h) {
        h = mergeSortList(h);
    }

    /*
    Quick sort.

    Optimize:
    1. When array's size <= cutOff, use insertion sort
    2. Choose pivot by median-3's law

    @param arr the array to sort
    */
    static void quickSort(std::vector<T> &arr) {
        quickSort(arr, 0, arr.size() - 1);
    }

    /*
    Quick select: find the kth smallest element in array (k starts at 0)

    @param arr the array to find
    @param k the k in the description
    @return the kth smallest element
    */
    static T quickSelect(std::vector<T> &arr, int k) {
        quickSelect(arr, 0, arr.size() - 1, k);
        return arr[k];
    }

    /*
    Test the function of the class.

    Sample #1:
    8 79 6 56 2 0 5 44 29 31 157 31
    */
    static void test() {
        cout << "Test SortHelper:\n" << endl;
        cin.clear();
        std::vector<T> origin, arr;
        T tmp;
        cout << "Input elements for sorting: (EOF to end):\n";
        while (cin >> tmp) {
            origin.push_back(tmp);
        }
        arr = origin;
        insertionSort(arr);
        cout << "Insertion sort result:" << endl;
        print(arr);
        arr = origin;
        selectionSort(arr);
        cout << "Selection sort result:" << endl;
        print(arr);
        arr = origin;
        shellSort(arr);
        cout << "Shell sort result:" << endl;
        print(arr);
        arr = origin;
        mergeSort(arr);
        cout << "Merge sort result:" << endl;
        print(arr);
        arr = origin;
        quickSort(arr);
        cout << "Quick sort result:" << endl;
        print(arr);
        cin.clear();
        while (1) {
            unsigned k;
            cout << "Input kth element you want to find: ";
            cin >> k;
            if (arr.size() >= k + 1) {
                arr = origin;
                auto res = quickSelect(arr, k);
                cout << "The " << k << "th smallest element: "
                    << res << endl;
            } else {
                cout << "Out of range." << endl;
            }
        }
    }

private:

    /*
    Swap the value of two elements.

    @param a the first element
    @param b the second element
    */
    static void swap(T &a, T &b) {
        T tmp = a;
        a = b;
        b = tmp;
    }

    /*
    Print the arr content.

    @param arr the array to print
    */
    static void print(std::vector<T> arr) {
        for (const auto &e : arr) {
            cout << e << " ";
        }
        cout << endl;
    }

    /*
    Merge sort for array.

    @param arr the array to sort
    @param left the start index of the array to sort
    @param right the end index of the array to sort
    @param tmpArr a temp array used for sorting
    */
    static void mergeSortArray(std::vector<T> &arr,
                               int left,
                               int right,
                               std::vector<T> &tmpArr) {
        if (left < right) {
            int mid = (left + right) / 2;
            mergeSortArray(arr, left, mid, tmpArr);
            mergeSortArray(arr, mid + 1, right, tmpArr);
            // Merge two array
            int n = right - left + 1, tmpIndex = left;
            int leftPos = left, leftEnd = mid, rightPos = mid + 1, rightEnd = right;
            while (leftPos <= leftEnd && rightPos <= rightEnd) {
                if (arr[leftPos] < arr[rightPos]) {
                    tmpArr[tmpIndex++] = arr[leftPos++];
                } else {
                    tmpArr[tmpIndex++] = arr[rightPos++];
                }
            }
            // Copy remain elements of first half
            while (leftPos <= leftEnd) {
                tmpArr[tmpIndex++] = arr[leftPos++];
            }
            // Copy remain elements of second half
            while (rightPos <= rightEnd) {
                tmpArr[tmpIndex++] = arr[rightPos++];
            }
            // Copy tmp array to origin array
            for (int i = 0; i < n; ++i, --rightEnd) {
                arr[rightEnd] = tmpArr[rightEnd];
            }
        }
    }

    /*
    Merge sort for list.

    @param h the head of the list to sort
    @return the new head pointer after sorting
    */
    static ListNode* mergeSortList(ListNode *h) {
        if (!h || !h->next) {
            return h;
        }
        ListNode *mid = h, *tmp = h->next;
        while (tmp && tmp->next) {
            mid = mid->next;
            tmp = tmp->next->next;
        }
        ListNode *firstHalf, *secondHalf;
        secondHalf = mid->next;
        mid->next = nullptr;  // Cut down the list into two half
        firstHalf = mergeSortList(h);
        secondHalf = mergeSortList(secondHalf);
        return mergeTwoList(firstHalf, secondHalf);
    }

    /*
    Merge two lists.

    @param a the first list
    @param b the second list
    @return the head of the list after merging
    */
    static ListNode* mergeTwoList(ListNode *a, ListNode *b) {
        if (!a) {
            return b;
        } else if (!b) {
            return a;
        }
        if (!(a->val < b->val)) {
            ListNode *tmp = b->next;
            b->next = a;
            a = b;
            b = tmp;
        }
        a->next = mergeTwoLists(a->next, b);
        return a;
    }

    /*
    Choose the pivot for quick sorting.

    Algorithm: Median-of-Three Partitioning
    Let a[left] <= a[mid] <= a[right]
    and store pivot element in a[right - 1].

    @param a the array to sort
    @param left the start index of the array to sort
    @param right the end index of the array to sort
    @return the pivot element
    */
    static T choosePivot(std::vector<T> &a, int left, int right) {
        int mid = (left + right) / 2;
        if (a[mid] < a[left]) {
            swap(a[left], a[mid]);
        }
        if (a[right] < a[left]) {
            swap(a[left], a[right]);
        }
        if (a[right] < a[mid]) {
            swap(a[mid], a[right]);
        }
        swap(a[mid], a[right - 1]);
        return a[right - 1];
    }

    /*
    Quick sort.

    @param a the array to sort
    @param left the start index of the array to sort
    @param right the end index of the array to sort
    */
    static void quickSort(std::vector<T> &a, int left, int right) {
        if (left + 10 <= right) {
            T pivot = choosePivot(a, left, right);
            int i = left, j = right - 1;
            while (1) {
                while (a[++i] < pivot) {}
                while (pivot < a[--j]) {}
                if (i < j) {
                    swap(a[i], a[j]);
                } else {
                    break;
                }
            }
            swap(a[i], a[right - 1]);  // Restore pivot
            quickSort(a, left, i - 1);
            quickSort(a, i + 1, right);
        } else {  // Use insertion sort for small array
            for (int i = left + 1; i <= right; ++i) {
                if (a[i - 1] > a[i]) {
                    T tmp = a[i], j = i;
                    while (j >= 1 && a[j - 1] > tmp) {
                        a[j] = a[j - 1];
                        --j;
                    }
                    a[j] = tmp;
                }
            }
        }
    }

    /*
    Quick select: find the kth smallest element in array (k starts at 0)
    After execution, a[k] is the kth smallest element

    @param a the array to sort
    @param left the start index of the array to sort
    @param right the end index of the array to sort
    @param k the k in the description
    */
    static void quickSelect(std::vector<T> &a, int left, int right, int k) {
        if (left + 10 <= right) {
            int pivot = choosePivot(a, left, right);
            int i = left, j = right - 1;
            while (1) {
                while (a[++i] < pivot) {}
                while (pivot < a[--j]) {}
                if (i < j) {
                    swap(a[i], a[j]);
                } else {
                    break;
                }
            }
            swap(a[i], a[right - 1]);
            if (k < i) {
                quickSelect(a, left, i - 1, k);
            } else if (k > i) {
                quickSelect(a, i + 1, right, k);
            }
        } else {  // Use insertion sort for small array
            for (int i = left + 1; i <= right; ++i) {
                if (a[i - 1] > a[i]) {
                    T tmp = a[i], j = i;
                    while (j >= 1 && a[j - 1] > tmp) {
                        a[j] = a[j - 1];
                        --j;
                    }
                    a[j] = tmp;
                }
            }
        }
    }
};

}
