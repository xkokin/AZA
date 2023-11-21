// Hlib Kokin 117991

#include<iostream>
#include<vector>
#include<algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<int> schedule(int n, vector<vector<int>> matrix) {
    vector<int> res(n);
    vector<int> taken(n, -1); // contains indexes of jobs that are taken


    vector<int> free_jobs(n);
    // this cyclus will be O(n)
    for (int i = 0; i < n; i++) {
        free_jobs[i] = i;
    }

    for (int p = 0; p < n; p++) {       // check person
        int min_val = 30;               // value that will contain min and initialized with the biggest value, which cannot be in matrix
        int min_index = -1;             // index of the job that will be the best
        int erase_index = -1;
        for (int j = 0; j < free_jobs.size(); j++) {   // check job one by one
            if (matrix[p][free_jobs[j]] < min_val) {   // if job is smaller than minimum - we take a closer look
                min_val = matrix[p][free_jobs[j]]; // set new minimum value
                min_index = free_jobs[j];          // and index
                erase_index = j;
            }
        }
        res[p] = min_index + 1; // add to result
        taken[p] = min_index; // add to taken
        free_jobs.erase(free_jobs.begin() + erase_index); // shrink our free jobs vector

    }

    // Outer cycle is O(n), Inner as well O(n), which makes it O(n^2),
    // first cycle with assigning free_jobs indexes doesn't influence the common complexity since it is faster than
    // main cycle


    return res;
}

int main () {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(0)));

    // Input the size of the matrix
    int n;
    cout << "Enter the size of the matrix (n): ";
    cin >> n;

    // Create and initialize the matrix with random numbers
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 15 + 1;  // Generates a random number between 1 and 15
        }
    }

    // Print the matrix to the console
    cout << "Generated Matrix:" << endl;
    // Print column indices (J1, J2, J3, ...)
    cout << "\t";
    for (int j = 1; j <= n; ++j) {
        cout << "J" << j << "\t";
    }
    cout << endl;

    for (int i = 0; i < n; ++i) {
        cout << "P" << i + 1 << "\t"; // Print row index
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;

        for (int k = 0; k < n * 9; ++k) {
            cout << "-";
        }
        cout << endl;
    }

    vector<int> res = schedule(n, matrix);

    for (int i: res) {
        cout << i << "; ";
    }
    cout << endl;
}

