#include <iostream>
#include <cmath>
using namespace std;

// Define the function for which we are finding the root
double f(double x) {
    return x * exp(x) - sin(x);
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

// Regula-Falsi method implementation
void regulaFalsi(double a, double b, double tolerance, int maxIterations) {
    if (f(a) * f(b) >= 0) {
        cout << "Invalid interval. f(a) and f(b) must have opposite signs." << endl;
        return;
    }

    double c; // Point of intersection
    for (int i = 0; i < maxIterations; ++i) {
        // Calculate the point of intersection
        c = (a * f(b) - b * f(a)) / (f(b) - f(a));
        double fc = f(c);

        // Print the current step
        cout << "Iteration " << i + 1 << ": c = " << c << ", f(c) = " << fc << endl;

        // Check if the root is found or if the interval is within tolerance
        if (fabs(fc) < tolerance) {
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

    // Call the Regula-Falsi method
    regulaFalsi(interval.first, interval.second, tolerance, maxIterations);

    return 0;
}