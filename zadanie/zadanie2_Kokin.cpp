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

void makeset(int i) { // O(1)
    U[i].parent = i;
    U[i].depth = 0;
    U[i].smallest = i;
}

void initial(int i) { // O(n)
    index ind;
    // creates i + 1 sets
    for(ind = 0; ind <= i; ind++) {
        makeset(ind);
    }
}

bool equal(set_pointer p, set_pointer q) { // O(1)
    if (p == q) {
        return true;
    }
    else {
        return false;
    }
}

void merge(set_pointer p, set_pointer q) {
    // if both sets are at the same depth and q set doesn't already have parent
    if (U[p].depth == U[q].depth && equal(U[q].parent, q)) { // O(1)
        U[p].depth = U[p].depth + 1;
        U[q].parent = p;
        if (U[q].smallest < U[p].smallest) {
            U[p].smallest = U[q].smallest;
        }
    }
    // either depths of sets are not the same or q set has parent that is not q itself
    else if (U[p].depth <= U[q].depth) { // O(nlgn)
        U[p].parent = q;

        // update smallest member of the set in the root
        while (U[p].smallest < U[q].smallest) { // O(nlgn)  thanks to depth attribute
            U[q].smallest = U[p].smallest;
            index parent = U[q].parent;
            p = q;
            q = parent;
        }
    }
    // p set is deeper
    else { //O (1)
        U[q].parent = p;
        if (U[q].smallest < U[p].smallest) {
            U[p].smallest = U[q].smallest;
        }
    }
}

int small(set_pointer p) { // O(1)
    return U[p].smallest;
}

set_pointer find(int s)
{
    index j;

    j = s;
    while(U[j].parent != j) { // O(n)
        j = U[j].parent;
    }
    return j;
}

int get_max_deadline(vector<vector<int>> input)
{
    int max = INT_MIN;
    for (int i = 0; i < n; i++) // O(n)
        if (max <  input[i][1]) {
            max = input[i][1];
        }
    return max;
}

void schedule(vector<vector<int>> input) {

    int d = get_max_deadline(input);
    // creates d + 1 sets
    initial(d);

    // go through all jobs
    for (int i = 1; i <= n; i++)
    {
        // maximum available free slot for this job
        // input[i][1] - deadline of the first job
        set_pointer availableSlot = find(input[i][1]); // O(n)
        // smallest member of the found set
        int availableSlotSmallest = small(availableSlot); // O(1)

        // If smallest available slot is not 0 (what would mean that no free slots left for this deadline)
        // then proceed to scheduling
        if (availableSlotSmallest > 0)
        {
            // merge sets of currently selected one and smaller (earlier set beside it)
            merge(find(availableSlotSmallest - 1), availableSlotSmallest); // O(nlgn)
            cout << "job number " << input[i][0] << " at day " << availableSlotSmallest << "; " << endl;
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

    schedule(input); // the biggest complexity is O(nlgn)
}

