//// Hlib Kokin 117991
//#include <iostream>
//#include <chrono>
//#include <vector>
//
//using namespace std;
//
//#define INF 999999999
//
//int fib16(int n) {
//
//    if (n <= 1) {
//        return n;
//    }
//    else {
//        return fib16(n-1) + fib16(n-2);
//    }
//}
//
//int fib17(int n) {
//    int i;
//    int f[n];
//
//    f[0]=0;
//    if(n > 0) {
//        f[1] = 1;
//        for (i = 2; i <= n; i++) {
//            f[i] = f[i - 1] + f[i - 2];
//        }
//    }
//    return f[n];
//}
//
//int priklad2(const std::vector<int>& arr, int target) {
//    int left = 0;
//    int right = arr.size() - 1;
//
//
//    while (left <= right) {
//        // rozdelime na tretiny
//        int sublistSize = (right - left + 1) / 3;
//        // 1/3
//        int mid1 = left + sublistSize;
//        // 2/3
//        int mid2 = right - sublistSize;
//
//        //nasli sme ciel
//        if (arr[mid1] == target) {
//            return mid1;
//        }
//        else if (arr[mid2] == target) {
//            return mid2;
//        }
//        // ciel je v prvej tretine
//        else if (target < arr[mid1]) {
//            right = mid1 - 1;
//        }
//        // ciel je v 3 tretine
//        else if (target > arr[mid2]) {
//            left = mid2 + 1;
//        }
//        // ciel je v druhej tretine
//        else {
//            left = mid1 + 1;
//            right = mid2 - 1;
//        }
//    }
//
//    return -1; // ciel nie je
//}
//
//int priklad3(int n, const std::vector<int>& A) {
//    int i, j = 0, k;
//
//    for (i = 1; i <= n; i++) {
//        j = j + A[i];
//    }
//    k = 1;
//    for (i = 1; i <= n; i++) {
//        k = k + k;
//    }
//
//    return j + k;
//}
//
//std::pair<int, int> priklad4(std::vector<std::vector<int>>& S, int n, int m, int kluc) {
//    int x = 0;  // zacnime od 1 riadku
//    int y = m - 1;  // a posledneho stlpca
//
//    while (x < n && y >= 0) {
//        if (S[x][y] == kluc)
//            return std::make_pair(x, y);  // Key found
//
//        if (S[x][y] < kluc)
//            x++;  // ideme dole o 1
//        else
//            y--;  // ideme vlavo o 1
//    }
//
//    return std::make_pair(0, 0);  // Key not found
//}
//
//int main() {
//    using std::chrono::high_resolution_clock;
//    using std::chrono::duration_cast;
//    using std::chrono::duration;
//    using std::chrono::milliseconds;
//
//    //  priklad 1
//    int pr1;
//    std::cout << "Enter number of iterations:\n";
//    std::cin >> pr1;
//    auto t1 = high_resolution_clock::now();
//    printf("fib16 for %d: %d\n", pr1, fib16(pr1));
//    // n = 49 je maximalna hodnota n pri ktorej fib16 sa skonci skor ako 60 s
//    // n = 49, time = 42 s
//    // n = 50, time = 63 s
//    auto t2 = high_resolution_clock::now();
//    duration<double, std::milli> ms_double = t2 - t1;
//    cout << "time: " << ms_double.count() << ";" << endl;
//    t1 = high_resolution_clock::now();
//    printf("fib17 for %d: %d\n", pr1, fib17(pr1));
//    // fib17 ide rychlejsie, pri n = 49 a n = 50 ma skoro rovnaky vysledok, cca 1.5 s - 2 s
//    t2 = high_resolution_clock::now();
//    ms_double = t2 - t1;
//    cout << "time: " << ms_double.count() << ";" << endl;
//
//    // priklad 2
//    // kedze my delime nas array na 3 sublisty vo while loop - mame zlozitost log3n
//    // (v binarnom strome mali y sme log2n, kde 3 a 2 su base resp.)
//    // Teda Zlozitost je O(logn), kedze base je konstanta
//    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
//    int target = 11;
//
//    int result = priklad2(arr, target);
//
//    if (result != -1) {
//        std::cout << "Item found at index " << result << std::endl;
//    } else {
//        std::cout << "Item not found" << std::endl;
//    }
//
//    // priklad3
//    // a) 55
//    // b) prva sluzka prejde iterativne n krat a teda jej zlozitost je O(n), druha slucka prejde uplne rovnako n krat, jej
//    // zlozitost je tiez O(m), T(n) = 2n kedze sa slucky prejdy jedna po jednej,
//    // O(T(n)) = O(n) + O(n) = O(n)
//    // c) kedze obe slucky maju rovnaky pocet iteraci, tak dame vsetko do jednej sluzcky a skratime T(n) = n, ale O(T(n)) pri tom zostane O(m)
//    vector<int> A = {2, 5, 3, 7, 8};
//    int num = 5;
//
//    cout << priklad3(num, A) << std::endl;
//
//
//    // priklad 4
//    // b) v najhorsom pripade neprejdeme kazdym riadkom a stlpcom kedze zaciname v pravom hornom rohu a ked kluc je vacsi ako
//    // aktualna hodnota - posuneme sa dole o 1 riadok, inac posuneme sa vlavo o 1 stlpec, tym padom zlozitost bude
//    // nie O(n * m) ale O(n + m)
//    int n, m, key;
//    std::cout << "Enter the number of rows: ";
//    std::cin >> n;
//    std::cout << "Enter the number of columns: ";
//    std::cin >> m;
//
//    std::vector<std::vector<int>> array(n, std::vector<int>(m));
//    std::cout << "Enter the sorted 2D array elements: \n";
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            std::cin >> array[i][j];
//        }
//    }
//
//    std::cout << "Enter the key to search: ";
//    std::cin >> key;
//
//    std::pair<int, int> res = priklad4(array, n, m, key);
//
//    if (res.first == 0 && res.second == 0)
//        std::cout << "Key not found.\n";
//    else
//        std::cout << "Key found at index pair (" << res.first << ", " << res.second << ")\n";
//}