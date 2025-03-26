#include <iostream>
#include <cmath>
using namespace std;

// Define the function for which we are finding the root
double f(double x) {
    return x*exp(x)-sin(x); // 2
}

// Bisection method implementation
void bisection(double a, double b, double tolerance, int maxIterations) {
    if (f(a) * f(b) >= 0) {
        cout << "Invalid interval. f(a) and f(b) must have opposite signs." << endl;
        return;
    }

    double c; // Midpoint
    for (int i = 0; i < maxIterations; ++i) {
        c = (a + b) / 2; // Calculate midpoint
        double fc = f(c);

        // Print the current step
        cout << "Iteration " << i + 1 << ": c = " << c << ", f(c) = " << fc << endl;

        // Check if the root is found or if the interval is within tolerance
        if (fabs(fc) < tolerance || (b - a) / 2 < tolerance) {
            cout << "Root found at x = " << c << " after " << i + 1 << " iterations." << endl;
            return;
        }

        // Narrow the interval
        if (f(a) * fc < 0) {
            b = c; // Root is in [a, c]
        } else {
            a = c; // Root is in [c, b]
        }
    }

    cout << "Maximum iterations reached. Approximate root is x = " << c << endl;
}

int main() {
    double a, b, tolerance;
    int maxIterations;

    // Input interval and parameters
    cout << "Enter the interval [a, b]: ";
    cin >> a >> b;
    cout << "Enter the tolerance: ";
    cin >> tolerance;
    cout << "Enter the maximum number of iterations: ";
    cin >> maxIterations;

    // Call the bisection method
    bisection(a, b, tolerance, maxIterations);

    return 0;
}
