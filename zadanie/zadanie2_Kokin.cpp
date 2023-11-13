// Hlib Kokin 117991

#include<iostream>
#include<vector>
using namespace std;

void copy_vector(vector<int> from, vector<int> *to) {
    for (int i : from) {
        to->push_back(i);
    }
}

vector<int> schedule(int n, vector<int> deadlines) {
    int d = 0;                          // d contains index of the job with latest deadline
    int d_value = 0;                    // d_value contains the value of the deadline
    bool can_append_result = true;
    bool can_append_deadline = false;   // shows us if the jobs index has been chosen to be added to result in
                                        // current iteration of inner loop
    int index = 2;
    vector<int> result(n + 1);
    vector<int> chosen_deadlines(n + 1);
    result[1] = 1;
    chosen_deadlines[1] = deadlines[1];


    for (int i = 2; i <= n; i++) {
        for (int deadline : chosen_deadlines) {
            if (deadline == deadlines[i]) {
                can_append_result = false;
                can_append_deadline = true;         // sets true only those which will not be considered for result
                break;
            }
        }
        if (deadlines[i] > d_value && can_append_deadline) {    // check if actual deadline[i] value is bigger and if it's already
                                                    // been added to result
            d = i;                                  // set index of the job with later deadline
            d_value = deadlines[i];                 // set value of the deadline
        }
        if (can_append_result) {
            result[index] = i;
            chosen_deadlines[index] = deadlines[i];
            index++;
        }
        else {
            can_append_result = true;
            can_append_deadline = false;
        }
    }
    if (d != 0 && d_value != 0 && index <= d_value) {       // if we have found such deadline that hasn't been taken yet
        result[index] = d;              // we append it to as the last one
    }
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
}

