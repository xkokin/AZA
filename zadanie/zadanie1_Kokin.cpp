// Hlib Kokin 117991

#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

void copy_vector(vector<int> from, vector<int> *to) {
    for (int i : from) {
        to->push_back(i);
    }
}

vector<vector<int>> schedule(int n, vector<vector<int>> input) {
    bool can_add = true;
    // let result be collection of jobs indexes,
    // its length could be less than n, because deadlines can overlap
    // let chosen_deadlines be a vector of deadlines that are already taken
    // as deadlines are sorted in decreasing order from the biggest job profit
    int index = 2;
    vector<vector<int>> result; // dvojrozmerne pole, kde 0 element je index deadlinu, 1 je deadline a 2 - profit
    result.resize(input.size());
    copy_vector(input[1], &result[1]);

    // we start from the i = 2, because 1st element is already the best option
    // outer loop is for n iterations, complexity is O(n)
    // inner loop is n iterations as well - O(n)
    // other operations are O(1)
    // so, the complexity is O(n) * O(n) = O(n^2)
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < index; j++) {
            if (result[j][1] == input[i][1]) {
                can_add = false;
                break;
            }
        }
        if (can_add) {
            copy_vector(input[i], &result[index]);
            index++;
        }
        else {
            can_add = true;
        }
    }
    result.erase(result.begin());
    result.resize(index-1);
    return result;
}

bool sortByProfit(const vector<int>& v1, const vector<int>& v2)
{
    return v1[2] > v2[2];
}

bool sortByDeadlines(const vector<int>& v1, const vector<int>& v2)
{
    if(!v1.empty() && !v2.empty()) {
        return v1[1] < v2[1];
    }
    else return false;
}

int main () {
    int n = 7;

    // 7, 1, 3 ,2
    vector<vector<int>> input = {
            {1, 2, 40},
            {2, 4, 15},
            {3, 3, 60},
            {4, 2, 20},
            {5, 3, 10},
            {6, 1, 45},
            {7, 1, 55}
    };

    // since implementation of the sorting algorithm is not part
    // of the assignment - I have desided to use already implemented function

    sort(input.begin(), input.end(), sortByProfit);  // sort complexity is O(nlogn)

    cout << "The Matrix after sorting is:\n";
    for (int i = 0; i < 7; i++) {           // complexity of these two cycles are O(n^2)
        for (int j = 0; j < 3; j++)
            cout << input[i][j] << " ";
        cout << endl;
    }

    input.insert(input.begin(), {0, 0, 0});

    vector<vector<int>> result = schedule(n, input);
    sort(result.begin(), result.end(), sortByDeadlines); // sort complexity is O(nlogn)
    for (int i = 0; i < result.size(); i++) {       // this whole cycle is O(n)
        if (result[i][0] != 0) {
            cout << result[i][0] << "; ";
        }
    }
    cout << endl;

    // although i used sort function (complexity of O(n)), the complexity of this whole code is O(n^2)
}

