// Hlib Kokin 117991

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


const int n = 7;
typedef int index;
typedef index set_pointer;


struct disjoint_set
{
    index parent;
    int depth;
    int smallest;

};


typedef disjoint_set universe[n];
universe U;

void makeset(int i) {
    U[i].parent = i;
    U[i].depth = 0;
    U[i].smallest = i;
}

void initial(int i) {
    index ind;

    for(ind = 0; ind <= i; ind++) {
        makeset(ind);
    }
}

void merge(set_pointer p, set_pointer q) {
    if (U[p].depth == U[q].depth) {
        U[p].depth = U[p].depth + 1;
        U[q].depth = U[p].depth + 1;
        if (U[q].smallest < U[p].smallest) {
            U[p].smallest = U[q].smallest;
        }
    }
    else if (U[p].depth < U[q].depth) {
        U[p].parent = q;
        if (U[p].smallest < U[q].smallest) {
            U[q].smallest = U[p].smallest;
        }
    }
    else {
        U[q].parent = p;
        if (U[q].smallest < U[p].smallest) {
            U[p].smallest = U[q].smallest;
        }
    }
}

int small(set_pointer p) {
    return U[p].smallest;
}

set_pointer find(int s)
{
    index j;

    j = s;
    while(U[j].parent != j) {
        j = U[j].parent;
    }
    return j;
}


void copy_vector(vector<int> from, vector<int> *to) {
    for (int i : from) {
        to->push_back(i);
    }
}

int get_max_deadline(vector<vector<int>> input)
{
    int ans = INT_MIN;
    for (int i = 0; i < n; i++)
        ans = max(ans, input[i][1]);
    return ans;
}

void schedule(vector<vector<int>> input) {

    int d = get_max_deadline(input);
    initial(d);

    // Traverse through all the jobs
    for (int i = 1; i <= n; i++)
    {
        // Find the maximum available free slot for
        // this job (corresponding to its deadline)
        int availableSlot = small(find(input[i][1]));

        // If maximum available free slot is greater
        // than 0, then free slot available
        if (availableSlot > 0)
        {
            // This slot is taken by this job 'i'
            // so we need to update the greatest
            // free slot. Note that, in merge, we
            // make first parameter as parent of
            // second parameter. So future queries
            // for availableSlot will return maximum
            // available slot in set of
            // "availableSlot - 1"
            merge(find(availableSlot - 1),
                     availableSlot);
            cout << availableSlot << " ; ";
        }
    }

}

bool sortByProfit(const vector<int>& v1, const vector<int>& v2)
{
    return v1[2] > v2[2];
}

int main () {

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
    for (int i = 0; i < n; i++) {           // complexity of these two cycles are O(n^2)
        for (int j = 0; j < 3; j++)
            cout << input[i][j] << " ";
        cout << endl;
    }

    input.insert(input.begin(), {0, 0, 0});

    schedule(input);
}

