#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip> // Include the iomanip library
using namespace std;

// Define the function for which we are finding the root
double f(double x) {
    return x * x - 2;
}

// Define the derivative of the function
double df(double x) {
    return 2*x ;
}

// Struct to represent an interval
struct Interval {
    double first;
    double second;
};

// Function to find all intervals where the root lies
vector<Interval> findIntervals(int start, int maxSteps, int numRoots) {
    vector<Interval> intervals;
    int foundRoots = 0;
    int i=0,j=0;
   while(maxSteps){
    // Search in positive direction
      if (f(i) * f(i + 1) < 0) {
            intervals.push_back({i, i + 1});
            foundRoots++;
        }
        i++;
        if(foundRoots==numRoots) {
            break;
        }

    // Search in negative direction
    
        if (f(j) * f(j- 1) < 0) {
            intervals.push_back({j - 1, j});
            foundRoots++;
        }
      j--;
        if(foundRoots==numRoots) {
                break;
            }
        maxSteps--;
   }
    return intervals;
}

// Newton-Raphson method implementation
void newtonRaphson(double x0, double tolerance, int maxIterations) {
    double x = x0;
    for (int i = 0; i < maxIterations; ++i) {
        double fx = f(x);
        double dfx = df(x);

        if (fabs(dfx) < 1e-10) {
            cout << "Derivative is too small. No convergence." << endl;
            return;
        }

        double x1 = x - fx / dfx;

        // Print the current step with precision up to 5 digits after the decimal point
        cout << fixed << setprecision(5);
        cout << "Iteration " << i + 1 << ": x = " << x1 << ", f(x) = " << f(x1) << endl;

        // Check if the root is found or if the interval is within tolerance
        if (fabs(x1 - x) < tolerance) {
            cout << "Root found at x = " << x1 << " after " << i + 1 << " iterations." << endl;
            return;
        }

        x = x1;
    }

    cout << "Maximum iterations reached. Approximate root is x = " << x << endl;
}

int main() {
    while (true) {
        int choice;
        cout << "Choose an option:" << endl;
        cout << "1. Newton-Raphson method with initial approximation" << endl;
        cout << "2. Newton-Raphson method without initial approximation" << endl;
        cout << "3. Exit" << endl;
        cin >> choice;

        if (choice == 3) {
            break;
        }

        double tolerance;
        int maxIterations;
        cout << "Enter the tolerance: ";
        cin >> tolerance;
        cout << "Enter the maximum number of iterations: ";
        cin >> maxIterations;

        if (choice == 1) {
            double x0;
            cout << "Enter the initial approximation: ";
            cin >> x0;
            newtonRaphson(x0, tolerance, maxIterations);
        } else if (choice == 2) {
            int start = 0, maxSteps, numRoots;
            cout << "Enter the maximum number of steps for interval search: ";
            cin >> maxSteps;
            cout << "Enter the number of roots to find: ";
            cin >> numRoots;

            // Find all intervals where the root lies
            vector<Interval> intervals = findIntervals(start, maxSteps, numRoots);
            if (intervals.empty()) {
                cout << "No intervals found where the function changes sign." << endl;
            } else {
                for (int  i = 0; i < intervals.size(); ++i) {
                    // Use the midpoint of the interval as the initial approximation
                    double x0 = (intervals[i].first + intervals[i].second) / 2;
                    cout << "Using interval [" << intervals[i].first << ", " << intervals[i].second << "]" << endl;
                    newtonRaphson(x0, tolerance, maxIterations);
                }
            }
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}