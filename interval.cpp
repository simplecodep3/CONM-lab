#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Define the function for which we are finding the root
double f(double x) {
    return x*x*x-5*x*x+6*x-1;
}

// Function to find a specified number of integer intervals where the root lies
vector<pair<int, int>> findIntervals(int start, int numIntervals) {
    vector<pair<int, int>> intervals;
    int step = 1;
    int foundIntervals = 0;
    int i=0;
    int j=0;

    // Search in positive direction
          while(foundIntervals<numIntervals) {
              if (f(i) * f(i + 1) < 0) {
            intervals.push_back(make_pair(i, i + 1));
            foundIntervals++;
            if (foundIntervals >= numIntervals) break;
        }
        i++;
        // Search in negative direction
 
        if (f(j) * f(j - 1) < 0) {
            intervals.push_back(make_pair(j- 1, j));
            foundIntervals++;
            if (foundIntervals >= numIntervals) break;
        }
         j--;

    }

    return intervals;
}

int main() {
    int start = 0, numIntervals;

    // Input number of intervals to find
    cout << "Enter the number of intervals to find: ";
    cin >> numIntervals;

    // Find intervals
    vector<pair<int, int>> intervals = findIntervals(start, numIntervals);

    // Print intervals
    if (!intervals.empty()) {
        cout << "Intervals where roots lie:" << endl;
        for (const auto& interval : intervals) {
            cout << "[" << interval.first << ", " << interval.second << "]" << endl;
        }
    } else {
        cout << "No intervals found where roots lie in the given range." << endl;
    }

    return 0;
}