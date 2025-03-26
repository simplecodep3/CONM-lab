#include <iostream>
#include <cmath>
using namespace std;

// Define the function for which we are finding the root
double f(double x) {
    return x * x - 4; // Example: f(x) = x^2 - 4
}

// Find a valid interval [a, b] where f(a) * f(b) < 0
bool findInterval(double& a, double& b, double start, double step, int maxSteps) {
    a = start;
    b = start + step;

    for (int i = 0; i < maxSteps; ++i) {
        if (f(a) * f(b) < 0) {
            return true; // Found a valid interval
        }
        a = b;
        b = a + step;
    }

    return false; // Interval not found
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
    double a, b, tolerance, start, step;
    int maxIterations, maxSteps;

    // Input parameters
    cout << "Enter the starting point for interval search: ";
    cin >> start;
    cout << "Enter the step size for interval search: ";
    cin >> step;
    cout << "Enter the maximum number of steps for interval search: ";
    cin >> maxSteps;
    cout << "Enter the tolerance: ";
    cin >> tolerance;
    cout << "Enter the maximum number of iterations: ";
    cin >> maxIterations;

    // Find a valid interval
    if (findInterval(a, b, start, step, maxSteps)) {
        cout << "Valid interval found: [" << a << ", " << b << "]" << endl;
        bisection(a, b, tolerance, maxIterations);
    } else {
        cout << "Failed to find a valid interval. Try adjusting the start point, step size, or max steps." << endl;
    }

    return 0;
}
