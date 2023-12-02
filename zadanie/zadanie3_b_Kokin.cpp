#include <iostream>
#include <vector>
#include <climits>
#include <Windows.h>

using namespace std;

enum LineType { NONE, HORIZONTAL, VERTICAL };

class Line {
public:
    int lineIndex;
    LineType rowType;

    Line(int lineIndex, LineType rowType) : lineIndex(lineIndex), rowType(rowType) {}

    LineType getLineType() {
        return rowType;
    }

    int getLineIndex() {
        return lineIndex;
    }

    bool isHorizontal() {
        return rowType == HORIZONTAL;
    }
};

bool isZero(const vector<int>& array) {             // O(n)
    for (int e : array) {
        if (e != 0) {
            return false;
        }
    }
    return true;
}


void print_matrix(vector<vector<int>>& matrix) {    //O(n^2)
    int rows, cols;
    rows = cols = matrix.size() - 1;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "\t";
    for (int j = 1; j <= cols; ++j) {
        cout << "J" << j << "\t";
    }
    cout << endl;
    for (int i = 1; i <= rows; ++i) {
        cout << "P" << i << "\t"; // row index
        for (int j = 1; j <= cols; ++j) {
            if (matrix[i][j] == 0) {
                SetConsoleTextAttribute(hConsole, 9);
                cout << matrix[i][j] << "\t";
                SetConsoleTextAttribute(hConsole, 7);
            }
            else {
                cout << matrix[i][j] << "\t";
            }
        }
        cout << endl;

        for (int k = 0; k < rows * 9; ++k) {
            cout << "-";
        }
        cout << endl;
    }
}

void print_matrix_assignment(vector<vector<int>>& matrix, vector<int>& res) {    //O(n^2)
    int rows, cols;
    rows = cols = matrix.size() - 1;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "\t";
    for (int j = 1; j <= cols; ++j) {
        cout << "J" << j << "\t";
    }
    cout << endl;
    for (int i = 1; i <= rows; ++i) {
        cout << "P" << i << "\t"; // row index
        for (int j = 1; j <= cols; ++j) {
            if (res[i] == j) {
                SetConsoleTextAttribute(hConsole, 4);
                cout << matrix[i][j] << "\t";
                SetConsoleTextAttribute(hConsole, 7);
            }
            else {
                cout << matrix[i][j] << "\t";
            }
        }
        cout << endl;

        for (int k = 0; k < rows * 9; ++k) {
            cout << "-";
        }
        cout << endl;
    }
}


void reductionByMax(vector<vector<int>>& matrix) {      // O(n^2)
    int rows, cols;
    rows = cols = matrix.size() - 1 ;
    int max_val = -1;

    for (int i = 1; i <= rows; ++i) {                    // O(n)
        for (int j = 1; j <= cols; ++j) {                // O(n)
            max_val = max(max_val, matrix[i][j]);
        }
    }

    for (int i = 1; i <= rows; ++i) {                    // O(n)
        for (int j = 1; j <= cols; ++j) {                // O(n)
            matrix[i][j] = max_val - matrix[i][j];
        }
    }

}

void rowReduction(vector<vector<int>>& matrix) {        // O(n^2)
    int rows, cols;
    rows = cols = matrix.size() - 1;

    for (int i = 1; i <= rows; ++i) {                    // O(n)
        // minimum element in the current row
        int min_val = INT_MAX;
        for (int j = 1; j <= cols; ++j) {                // O(n)
            min_val = min(min_val, matrix[i][j]);
        }

        // subtract the minimum from each element
        for (int j = 1; j <= cols; ++j) {                // O(n)
            matrix[i][j] -= min_val;
        }
    }
}


void columnReduction(vector<vector<int>>& matrix) {     // O(n^2) by analogy with rowReduction
    int rows, cols;
    rows = cols = matrix.size() - 1;

    for (int j = 1; j <= cols; ++j) {
        int min_val = INT_MAX;
        for (int i = 1; i <= rows; ++i) {
            min_val = min(min_val, matrix[i][j]);
        }

        for (int i = 1; i <= rows; ++i) {
            matrix[i][j] -= min_val;
        }
    }
}


// for purposes of step 3
vector<Line> getMinimumLines(vector<vector<int>>& matrix) {             // O(n^3)
    int rows, cols, n;
    n = rows = cols = matrix.size() - 1;
    vector<int> zeros_per_row(n + 1, 0);
    vector<int> zeros_per_col(n + 1, 0);

    // count the number of 0's per row and the number of 0's per column
    for (int i = 1; i <= rows; ++i) {           //O(n^2)
        for (int j = 1; j <= cols; ++j) {
            if (matrix[i][j] == 0) {
                zeros_per_row[i]++;
                zeros_per_col[j]++;
            }
        }
    }

    // there should be at least n lines,
    // initialize the list with an initial capacity of n
    vector<Line> lines;
    LineType last_inserted_line_type = NONE;

    // while there are 0's to count in either rows or columns
    while (!isZero(zeros_per_row) && !isZero(zeros_per_col)) {   //O(n^2) - because to check all zeroes we
                                                                            // have to check all cells of nXn matrix
        // search the largest count of 0's in both arrays
        int max = -1;
        Line line_with_most_zeros(0, HORIZONTAL);

        // if another count of 0's equal to "max" exists, prefer the one with the same direction as the last added line
        for (int i = 1; i <= rows; ++i) {                   //O(n)
            if (zeros_per_row[i] > max || (zeros_per_row[i] == max && last_inserted_line_type == HORIZONTAL)) {
                line_with_most_zeros = Line(i, HORIZONTAL);
                max = zeros_per_row[i];
            }
        }

        for (int i = 1; i <= cols; ++i) {                   //O(n)
            if (zeros_per_col[i] > max || (zeros_per_col[i] == max && last_inserted_line_type == VERTICAL)) {
                line_with_most_zeros = Line(i, VERTICAL);
                max = zeros_per_col[i];
            }
        }

        // delete the 0 count from the line
        if (line_with_most_zeros.isHorizontal()) {
            zeros_per_row[line_with_most_zeros.getLineIndex()] = 0;
        }
        else {
            zeros_per_col[line_with_most_zeros.getLineIndex()] = 0;
        }


        // once we've found the line (either horizontal or vertical) with the greater 0's count
        // iterate over its elements and subtract the 0's from the other lines
        int index = line_with_most_zeros.getLineIndex();
        if (line_with_most_zeros.isHorizontal()) {          //O(n)
            for (int j = 1; j <= cols; ++j) {
                if (matrix[index][j] == 0) {
                    zeros_per_col[j]--;
                }
            }
        } else {                                            //O(n)
            for (int j = 1; j <= rows; ++j) {
                if (matrix[j][index] == 0) {
                    zeros_per_row[j]--;
                }
            }
        }

        // add the line to the list of lines
        lines.push_back(line_with_most_zeros);
        last_inserted_line_type = line_with_most_zeros.getLineType();
    }
    return lines;
}


// for purposes of step 4
vector<vector<int>> addZeroes(vector<vector<int>>& matrix, vector<Line>& lines) { // O(n^2)
    int rows, cols, n;
    n = rows = cols = matrix.size() - 1;
    int min_val = INT_MAX;

    vector<int> rowsLined(n + 1, 0);
    vector<int> colsLined(n + 1, 0);

    // set the cols and rows that shouldn't be considered
    for (int i = 0; i < lines.size(); i++) {           // O(n)
        // if current line is horizontal then select row and  block it, so we
        // do not consider it furthermore
        if (lines[i].isHorizontal()) {
            rowsLined[lines[i].getLineIndex()] = -1;
        }
        // the same thing for cols
        else {
            colsLined[lines[i].getLineIndex()] = -1;
        }
    }

    // find the minimum value out of non-crossed by line values
    for (int i = 1; i <= rows; ++i) {                    // O(n)
        // if actual row is blocked - continue
        if (rowsLined[i] == -1) {
            continue;
        }

        for (int j = 1; j <= cols; ++j) {                // O(n)
            // if actual col is blocked - continue
            if (colsLined[j] == -1) {
                continue;
            }

            min_val = min(min_val, matrix[i][j]);
        }
    }

    cout << "Min value is " << min_val << endl;

    // add that min value to the double-crossed and subtract it from non-crossed
    for (int i = 1; i <= rows; ++i) {                    // O(n)
        for (int j = 1; j <= cols; ++j) {                // O(n)
            // if actual value is double-crossed - add min
            if (rowsLined[i] == -1) {
                if (colsLined[j] == -1) {
                    matrix[i][j] += min_val;
                }
            }
            // if actual value is not crossed - subtract
            else if (rowsLined[i] != -1) {
                if (colsLined[j] != -1) {
                    matrix[i][j] -= min_val;
                }
            }
        }
    }

    return matrix;
}


void hungarianAlgo(vector<vector<int>>& matrix, vector<vector<int>>& initMatrix) {
    int n, rows, cols, lines_cnt = 0;
    vector<Line> lines;

    n = rows = cols = matrix.size() - 1;

    // maximization of profit case
    reductionByMax(matrix);                 // O(n^2)
    // step 1
    rowReduction(matrix);                   // O(n^2)
    // step 2
    columnReduction(matrix);                // O(n^2)
    // print matrix after all reductions
    cout << "Matrix after reductions: " << endl;
    print_matrix(matrix);                   // O(n^2)
    // step 3 - check if minimum of lines that cover all zeroes is equal to number of rows/columns
    while (lines_cnt != n) {
        lines = getMinimumLines(matrix);    // O(n^3)
        lines_cnt = lines.size();
        cout << "Minimum number of lines is " << lines_cnt << endl;
        //step 4 - add additional zeroes
        if (lines_cnt != n) {
            matrix = addZeroes(matrix, lines);   // O(n^2)
            print_matrix(matrix);
        }
    }

    // print assignment order
    cout << "Assignment order is: ";
    vector<int> bannedCols(n + 1, 0);
    vector<int> res(n + 1, 0);
    int assigned = 0;
    int profit = 0;

    for (int i = 1; i <= rows; i++) {   // O(n^2)
        for (int j = 1; j <= cols; j++) {
            if (bannedCols[j] != -1 && matrix[i][j] == 0) {
                profit += initMatrix[i][j];
                res[i] = j;
                bannedCols[j] = -1;
                assigned += 1;
                break;
            }
        }
    }

    if (assigned != n) {
        assigned = 0;
        fill(bannedCols.begin(), bannedCols.end(), 0);
        for (int i = 1; i <= rows; i++) {   // O(n^2)
            for (int j = cols; j >= 1; j--) {
                if (bannedCols[j] != -1 && matrix[i][j] == 0) {
                    profit += initMatrix[i][j];
                    res[i] = j;
                    bannedCols[j] = -1;
                    assigned += 1;
                    break;
                }
            }
        }
        if (assigned != n) {
            assigned = 0;
            fill(bannedCols.begin(), bannedCols.end(), 0);
            for (int i = rows; i >= 1; i--) {   // O(n^2)
                for (int j = cols; j >= 1; j--) {
                    if (bannedCols[j] != -1 && matrix[i][j] == 0) {
                        profit += initMatrix[i][j];
                        res[i] = j;
                        bannedCols[j] = -1;
                        assigned += 1;
                        break;
                    }
                }
            }
            if (assigned != n) {
                assigned = 0;
                fill(bannedCols.begin(), bannedCols.end(), 0);
                for (int i = rows; i >= 1; i--) {   // O(n^2)
                    for (int j = 1; j <= cols; j++) {
                        if (bannedCols[j] != -1 && matrix[i][j] == 0) {
                            profit += initMatrix[i][j];
                            res[i] = j;
                            bannedCols[j] = -1;
                            assigned += 1;
                            break;
                        }
                    }
                }
            }
        }
    }

    for (int i = 1; i <= rows; i++) {
        cout << "P" << i << "-" << "J" << res[i] << "; ";
    }
    cout << endl << endl;

    print_matrix_assignment(initMatrix, res);

    cout << endl << "Total profit is " << profit << endl;
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

    print_matrix(initial_matrix);


    vector<pair<int, int>> assignmentOrder;
    hungarianAlgo(result_matrix, initial_matrix);

    return 0;
}
