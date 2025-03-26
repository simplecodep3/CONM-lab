#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Define the function for which we are finding the root
double f(double x) {
    return x * exp(x) - sin(x);
}

// Define the derivative of the function
double df(double x) {
    return exp(x) * (x + 1) - cos(x);
}

// Function to find an interval where the root lies
pair<double, double> findInterval(int start, int maxSteps) {
    for (int i = start; i < start + maxSteps; ++i) {
        if (f(i) * f(i + 1) < 0) {
            return make_pair(i, i + 1);
        }
    }
    for (int i = start; i > start - maxSteps; --i) {
        if (f(i) * f(i - 1) < 0) {
            return make_pair(i - 1, i);
        }
    }
    return make_pair(0, 0); // No interval found
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

        // Print the current step
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
    int start = 0, maxSteps;
    double tolerance;
    int maxIterations;

    // Input parameters
    cout << "Enter the maximum number of steps for interval search: ";
    cin >> maxSteps;
    cout << "Enter the tolerance: ";
    cin >> tolerance;
    cout << "Enter the maximum number of iterations: ";
    cin >> maxIterations;

    // Find an interval where the root lies
    pair<double, double> interval = findInterval(start, maxSteps);
    if (interval.first == 0 && interval.second == 0) {
        cout << "No interval found where the function changes sign." << endl;
        return 0;
    }

    // Use the midpoint of the interval as the initial approximation
    double x0 = (interval.first + interval.second) / 2;

    // Call the Newton-Raphson method
    newtonRaphson(x0, tolerance, maxIterations);

    return 0;
}