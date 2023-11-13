//// Hlib Kokin 117991
////spravil som 1, 2 a 4
//#include <iostream>
//#include <cmath>
//#include <vector>
//
//using namespace std;
//
//bool promising (int i, vector<int>col) {
//    int k = 1;
//    bool switch_ = true;
//
//    while (k < i && switch_) {
//        if (col[i] == col[k] || abs(col[i] - col[k]) == i - k) {
//            switch_ = false;
//        }
//        k++;
//    }
//    return switch_;
//}
//
//void queens(int i, vector<int>col, int n) {
//
//    if (promising(i, col)) {
//        if (i == n) {
//            for (int k = 1; k <= n; k++) {
//                cout << col[k] << " ";
//            }
//            cout << endl;
//            // vypis 2D
//            for (int k = 1; k <= n; k++) {
//                for (int l = 1; l <= n; l++) {
//                    if (col[k] == l) {
//                        cout << " Q ";
//                    } else {
//                        cout << " - ";
//                    }
//                }
//                printf("\n");
//            }
//        }
//        else {
//            for (int j = 1; j <= n; j++) {
//                col[i + 1] = j;
//                queens(i + 1, col, n);
//            }
//        }
//    }
//}
//
//bool promising2(int i, int weight, int total, vector<int> w, int W) {
//    return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
//}
//
//void sum_of_subsets(int i, int weight, int total, vector<int> w, int W, vector<string> include) {
//    if (promising2(i, weight, total, w, W)) {
//        if (weight == W) {
//            for (int j = 1; j <= i; j++) {
//                cout << include[j] << " ";
//            }
//            cout << endl;
//        }
//        else {
//            include[i + 1] = "yes";
//            sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1], w, W, include);
//            include[i + 1] = "no";
//            sum_of_subsets(i + 1, weight, total - w[i + 1], w, W, include);
//        }
//    }
//}
//
//
//
//int main () {
//
//    int n;
//    cout << "queens: Zadajte n:\n";
//    cin >> n;
//
//    vector<int> col(n+1);
//
//    queens(0, col, n);
//
//    cout << "sum-of-subsets: Zadajte n:\n";
//    cin >> n;
//    vector<int> w(n + 1);
//    int total = 0;
//    cout << "sum-of-subsets: Zadajte list dlzky n:\n";
//    for (int i = 1; i <= n; i++) {
//        cin >> w[i];
//        total += w[i];
//    }
//    int W;
//    cout << "sum-of-subsets: Zadajte W:\n";
//    cin >> W;
//
//
//    vector<string> include(n + 1);
//    sum_of_subsets(0, 0, total, w, W, include);
//
//}
