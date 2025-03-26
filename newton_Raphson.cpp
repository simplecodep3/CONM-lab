#include <iostream>
#include <cmath>
using namespace std;

// Define the function for which we are finding the root
double f(double x) {
    return x * exp(x) - sin(x);
}

// Define the derivative of the function
double df(double x) {
    return exp(x) * (x + 1) - cos(x);
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
    double x0, tolerance;
    int maxIterations;

    // Input initial guess and parameters
    cout << "Enter the initial guess: ";
    cin >> x0;
    cout << "Enter the tolerance: ";
    cin >> tolerance;
    cout << "Enter the maximum number of iterations: ";
    cin >> maxIterations;

    // Call the Newton-Raphson method
    newtonRaphson(x0, tolerance, maxIterations);

    return 0;
}