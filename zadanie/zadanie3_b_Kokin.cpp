#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;


void step3() {

}

void print_matrix(vector<vector<int>>& printMatrix, int n) {
    cout << "\t";
    for (int j = 1; j <= n; ++j) {
        cout << "J" << j << "\t";
    }
    cout << endl;
    for (int i = 1; i <= n; ++i) {
        cout << "P" << i << "\t"; // row index
        for (int j = 1; j <= n; ++j) {
            cout << printMatrix[i][j] << "\t";
        }
        cout << endl;

        for (int k = 0; k < n * 9; ++k) {
            cout << "-";
        }
        cout << endl;
    }
}

// find maximum matching in bipartite graph using Hungarian algorithm
void schedule(vector<vector<int>>& costMatrix, vector<pair<int, int>>& assignmentOrder, int n) {
    vector<vector<int>> DP(n+1, vector<int>(n+1, 0));
    for(int person = 1; person <= n; person++){
        for(int job = 1; job <= n; job++){
            // try to assign k workers to the jth project
            for(int act = 1; act <= person; act++){
                DP[person][job] =
                        max(DP[person][job], costMatrix[act][job] + DP[person - act][job - 1]);
            }
        }
    }
    cout << "result_matrix" << endl;
    print_matrix(DP, n);
}

int main() {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(0)));

    // Input the size of the matrix
    int n;
    cout << "Enter the size of the matrix (n): ";
    cin >> n;

    // Create and initialize the matrix with random numbers
    vector<vector<int>> initial_matrix(n+1, vector<int>(n+1));
    vector<vector<int>> result_matrix(n+1, vector<int>(n+1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int random = rand() % 15 + 1;  //random number between 1 and 15
            initial_matrix[i][j] = random;
            result_matrix[i][j] = random;
        }
    }

    cout << "initial matrix:" << endl;

    print_matrix(initial_matrix, n);


    vector<pair<int, int>> assignmentOrder;
    schedule(result_matrix, assignmentOrder, n);
//
//    int cost = 0;
//    for (const auto& pair : assignmentOrder) {
//        cost += initial_matrix[pair.first][pair.second];
//    }
//
//    cout << "Best combination will cost " << cost << endl;
//
//    for (int i = 0; i < assignmentOrder.size(); i++) {
//        cout << "P" << assignmentOrder[i].first + 1 << ": " << assignmentOrder[i].second + 1 << " ; ";
//
//    }

    return 0;
}
