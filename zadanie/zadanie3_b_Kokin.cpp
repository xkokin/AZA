#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;


void step3() {

}



// find maximum matching inbipartite graph using Hungarian algorithm
void schedule(vector<vector<int>>& costMatrix, vector<pair<int, int>>& assignmentOrder) {
    int n = costMatrix.size();
    int m = costMatrix[0].size();

    // find minimum value in each row and substract it from each element of the row
    // O(n^2) <= outer loop is O(n) and there are two inner loops, they give O(n)+O(n) = O(n), which makes it O(n * n)
    for (int i = 0; i < n; i++) {   // O(n)
        int minVal = INF;
        for (int j = 0; j < m; j++) { // O(n)
            minVal = min(minVal, costMatrix[i][j]);
        }
        for (int j = 0; j < m; j++) { // O(n)
            costMatrix[i][j] -= minVal;
        }
    }

    // find min value in each column
    for (int j = 0; j < m; ++j) {
        int minVal = INF;
        for (int i = 0; i < n; ++i) {
            minVal = min(minVal, costMatrix[i][j]);
        }
        for (int i = 0; i < n; ++i) {
            costMatrix[i][j] -= minVal;
        }
    }

    // Step 3: Cover all zeros in the matrix with the minimum number of lines


    // Step 4: Try to find an assignment by finding a zero not covered by a line
    while (assignmentOrder.size() < n) {
        int row = -1, col = -1;

        // Find an uncovered zero
        for (int i = 0; i < n; ++i) {
            if (!rowCovered[i]) {
                for (int j = 0; j < m; ++j) {
                    if (!colCovered[j] && costMatrix[i][j] == 0) {
                        row = i;
                        col = j;
                        assignmentOrder.push_back({row, col});
                        rowCovered[row] = true;
                        colCovered[col] = true;
                        break;
                    }
                }
            }
            if (row != -1) {
                break;
            }
        }

        if (row == -1) {
            // No uncovered zero found, go to step 6
            break;
        }
    }

    // Step 5: Determine the smallest uncovered value (denoted by minVal)
    int minVal = INF;
    for (int i = 0; i < n; ++i) {
        if (!rowCovered[i]) {
            for (int j = 0; j < m; ++j) {
                if (!colCovered[j]) {
                    minVal = min(minVal, costMatrix[i][j]);
                }
            }
        }
    }

    // Step 6: Subtract minVal from all uncovered values and add minVal to all doubly covered values
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!rowCovered[i] && !colCovered[j]) {
                costMatrix[i][j] -= minVal;
            } else if (rowCovered[i] && colCovered[j]) {
                costMatrix[i][j] += minVal;
            }
        }
    }

    return;
}

int main() {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(0)));

    // Input the size of the matrix
    int n;
    cout << "Enter the size of the matrix (n): ";
    cin >> n;

    // Create and initialize the matrix with random numbers
    vector<vector<int>> initial_matrix(n, vector<int>(n));
    vector<vector<int>> result_matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int random = rand() % 15 + 1;  //random number between 1 and 15
            initial_matrix[i][j] = random;
            result_matrix[i][j] = random;
        }
    }

    cout << "initial matrix:" << endl;
    cout << "\t";
    for (int j = 1; j <= n; ++j) {
        cout << "J" << j << "\t";
    }
    cout << endl;

    for (int i = 0; i < n; ++i) {
        cout << "P" << i + 1 << "\t"; // row index
        for (int j = 0; j < n; ++j) {
            cout << initial_matrix[i][j] << "\t";
        }
        cout << endl;

        for (int k = 0; k < n * 9; ++k) {
            cout << "-";
        }
        cout << endl;
    }

    vector<pair<int, int>> assignmentOrder;
    schedule(result_matrix, assignmentOrder);

    int cost = 0;
    for (const auto& pair : assignmentOrder) {
        cost += initial_matrix[pair.first][pair.second];
    }

    cout << "Best combination will cost " << cost << endl;

    for (int i = 0; i < assignmentOrder.size(); i++) {
        cout << "P" << assignmentOrder[i].first + 1 << ": " << assignmentOrder[i].second + 1 << " ; ";

    }

    return 0;
}
