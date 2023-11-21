// Hlib Kokin 117991

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void copy_vector(vector<int> from, vector<int> *to) {
    for (int i : from) {
        to->push_back(i);
    }
}

vector<vector<int>> schedule(int n, vector<vector<int>> input) {
    // let result be collection of jobs indexes
    // as deadlines are sorted in decreasing order from the biggest job profit
    vector<vector<int>> result;                                 // dvojrozmerne pole, kde 0 element je index deadlinu, 1 je deadline a 2 - profit
    vector<int> empty_indexes(n+1);                          // let empty_indexes be a vector with states of indexes
    result.resize(input.size());
    copy_vector(input[1], &result[input[1][1]]);       // assign job to the index of deadline in result vector

    // we will initialize free indexes with number -1 on the deadline of the first element as it is already picked
    empty_indexes[input[1][1]] = -1;

    // we start from the i = 2, because 1st element is already the best option
    // outer loop is for n iterations, complexity is O(n)
    // inner is O(n) aswell, together they give us O(n^2)
    // other operations are O(1)
    // so, the complexity is O(n)
    for (int i = 2; i <= n; i++) {
        for(int j = input[i][1]; j > 0; j--) {
            if (empty_indexes[j] != -1) {
                copy_vector(input[i], &result[j]);
                empty_indexes[j] = -1;
                break;
            }
        }
    }
    result.erase(result.begin());
    result.resize(result.size() - 1);
    return result;
}

bool sortByProfit(const vector<int>& v1, const vector<int>& v2)
{
    return v1[2] > v2[2];
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

    std::sort(input.begin(), input.end(), sortByProfit);  // sort complexity is O(nlogn)

    cout << "The Matrix after sorting is:\n";
    for (int i = 0; i < 7; i++) {           // complexity of these two cycles are O(n^2)
        for (int j = 0; j < 3; j++)
            cout << input[i][j] << " ";
        cout << endl;
    }

    input.insert(input.begin(), {0, 0, 0});

    vector<vector<int>> result = schedule(n, input);
    for (int i = 0; i < result.size(); i++) {       // this whole cycle is O(n)
        if (!result[i].empty() && result[i][0] != 0) {
            cout << result[i][0] << "; ";
        }
    }
    cout << endl;

    // if on the input we will get already sorted table of jobs, then there is no need of using sort function,
    // that way we will get total time complexity of O(n)
}

