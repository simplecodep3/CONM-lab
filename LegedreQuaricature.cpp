#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;
// Function to be integrated - you can change this as needed
double function(double x) {
    return x * x * sin(x); // Example function: x^2 * sin(x)
}
// Calculate Legendre polynomial of degree n at point x
double legendrePolynomial(int n, double x) {
    if (n == 0) return 1.0;
    if (n == 1) return x;
    double p0 = 1.0;
    double p1 = x;
    double pn = 0.0;
    for (int i = 2; i <= n; i++) {
        pn = ((2 * i - 1) * x * p1 - (i - 1) * p0) / i;
        p0 = p1;
        p1 = pn;
    }
    return pn;
}

// Calculate derivative of Legendre polynomial of degree n at point x
double legendreDerivative(int n, double x) {
    if (n == 0) return 0.0;
    return n * (x * legendrePolynomial(n, x) - legendrePolynomial(n - 1, x)) / (x * x - 1.0);
}

// Find roots of Legendre polynomial using Newton-Raphson method
vector<double> findLegendreRoots(int n) {
    vector<double> roots;
    double tolerance = 1e-14;
    
    // Initial approximations for roots
    for (int i = 1; i <= n; i++) {
        // Initial guess based on formula
        double x = cos(M_PI * (i - 0.25) / (n + 0.5));
        
        // Newton-Raphson iterations
        double delta;
        do {
            delta = legendrePolynomial(n, x) / legendreDerivative(n, x);
            x = x - delta;
        } while (abs(delta) > tolerance);
        
        roots.push_back(x);
    }
    
    return roots;
}

// Calculate weights for Gauss-Legendre quadrature
vector<double> calculateWeights(int n, const vector<double>& roots) {
    vector<double> weights;
    
    for (double root : roots) {
        double derivative = legendreDerivative(n, root);
        double weight = 2.0 / ((1.0 - root * root) * derivative * derivative);
        weights.push_back(weight);
    }
    
    return weights;
}

// Perform Gauss-Legendre quadrature integration
double gaussLegendreQuadrature(double a, double b, int n) {
    // Find roots of Legendre polynomial
    vector<double> roots = findLegendreRoots(n);
    
    // Calculate weights
    vector<double> weights = calculateWeights(n, roots);
    
    // Display roots
    cout << "\nRoots of Legendre polynomial P" << n << "(x):" << endl;
    for (size_t i = 0; i < roots.size(); i++) {
        cout << "x[" << i + 1 << "] = " << setprecision(15) << roots[i] << endl;
    }
    
    // Display weights
    cout << "\nCorresponding weights:" << endl;
    for (size_t i = 0; i < weights.size(); i++) {
        cout << "w[" << i + 1 << "] = " << setprecision(15) << weights[i] << endl;
    }
    
    // Perform integration
    double sum = 0.0;
    for (size_t i = 0; i < roots.size(); i++) {
        // Transform from [-1, 1] to [a, b]
        double x = 0.5 * ((b - a) * roots[i] + a + b);
        sum += weights[i] * function(x);
    }
    
    // Scale the result
    sum *= 0.5 * (b - a);
    
    return sum;
}

int main() {
    double lowerLimit, upperLimit;
    int points;
    
    cout << "Numerical Integration using Gauss-Legendre Quadrature" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Function to integrate: x^2 * sin(x)" << endl;
    
    // Get user input
    cout << "\nEnter lower limit of integration: ";
    cin >> lowerLimit;
    
    cout << "Enter upper limit of integration: ";
    cin >> upperLimit;
    
    cout << "Enter number of quadrature points: ";
    cin >> points;
    
    // Validate input
    if (points <= 0) {
        cout << "Number of points must be positive. Using default value of 5." << endl;
        points = 5;
    }
    
    // Perform Gauss-Legendre quadrature
    double result = gaussLegendreQuadrature(lowerLimit, upperLimit, points);
    
    // Display result
    cout << "\nResult of integration: " << setprecision(15) << result << endl;
    
    return 0;
}