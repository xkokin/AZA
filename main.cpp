#include <iostream>
#define INF 999999999
using namespace std;


double max(const double *arr, unsigned size) {
    double max = 0;

    for (int i = 0; i < size; ++i) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }
    return max;
}

double min(const double *arr, unsigned size) {
    double min = INF;

    for (int i = 0; i < size; ++i) {
        if (min > arr[i]) {
            min = arr[i];
        }
    }
    return min;
}

double avg(const double *arr, unsigned size) {
    double sum = 0;

    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum / size;
}

double sum(const double *arr, unsigned size) {
    double sum = 0;

    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum;
}

void mystery(double * arr, unsigned size) {
    int x = 0;
    int y = (int)size-1;
    double temp;

    while (x < y) {
        temp = arr[x];
        arr[x] = arr[y];
        arr[y] = temp;
        x++;
        y--;
    }

    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

}

//int main() {
//
//    unsigned size;
//    cin >> size;
//    double arr[size];
//    for (int i = 0; i < size; ++i) {
//        cin >> arr[i];
//    }
//
//    cout << "max: " << max(arr, size) << endl;
//    cout << "min: " << min(arr, size) << endl;
//    cout << "avg: " << avg(arr, size) << endl;
//    cout << "sum: " << sum(arr, size) << endl;
//
//    mystery(arr, size);
//
//
//    return 0;
//}

