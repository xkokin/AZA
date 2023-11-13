//#include <iostream>
//#include <chrono>
////#include "matplotlibcpp.h"
//
//#define INF 999999999
//
////namespace plt = matplotlibcpp;
//using namespace std;
//
//double secondFunction(const int n) {
//    using std::chrono::high_resolution_clock;
//    using std::chrono::duration_cast;
//    using std::chrono::duration;
//    using std::chrono::milliseconds;
//
//    auto t1 = high_resolution_clock::now();
//    int sum = 0;
//    for (int i = 1; i < n; i*=2) { // log n
//        sum++;
//        for (int j = n; j > 0; j/=2){ // log n
//            sum++;
//            for (int k = j; k < n; k+=2) { // n
//                sum ++;
//            }
//        }
//    }
//    // celkovo n log n ^2
//    auto t2 = high_resolution_clock::now();
//    auto ms_int = duration_cast<milliseconds>(t2 - t1);
//    duration<double, std::milli> ms_double = t2 - t1;
//    cout << "time: " << ms_double.count() << "; ";
//
//    return (double)sum;
//}
//
//int main() {
//
//
////    vector<double> sums = {secondFunction(1), secondFunction(10), secondFunction(100), secondFunction(1000), secondFunction(10000)};
////    vector<double> n = {1, 10, 100, 1000, 10000};
////    plt::figure();
////    plt::plot(sums, n);
//
//
//    cout << "1: " << secondFunction(1) << "; 2: "
//    << secondFunction(10) << "; 3: "
//    << secondFunction(100) << "; 4: "
//    << secondFunction(1000) << "; 5: "
//    << secondFunction(10000);
//
//    return 0;
//}
//
//
//// 3 - n^3