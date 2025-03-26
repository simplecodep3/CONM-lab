#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// Function to be integrated
double f(double x) {
    return x*x; // Example function: x^2
}

// Gauss-Legendre Quadrature for up to 4 points
void gaussLegendreQuadrature(double a, double b, int n) {
    if (n < 1 || n > 4) {
        cout << "Error: Number of quadrature points must be between 1 and 4." << endl;
        return;
    }
    
    // Predefined roots and weights using vectors
    vector<vector<double>> xk = {
        {0.0},
        {-0.5773502692, 0.5773502692},
        {-0.7745966692, 0.0, 0.7745966692},
        {-0.8611363116, -0.3399810436, 0.3399810436, 0.8611363116}
    };
    
    vector<vector<double>> lambda_k = {
        {2.0},
        {1.0, 1.0},
        {0.5555555556, 0.8888888889, 0.5555555556},
        {0.3478548451, 0.6521451549, 0.6521451549, 0.3478548451}
    };
    
    double integral = 0.0;
    for (int i = 0; i < n; i++) {
        double xi = ((b - a) / 2.0) * xk[n-1][i] + (a + b) / 2.0;
        integral += lambda_k[n-1][i] * f(xi);
    }
    integral *= (b - a) / 2.0;
    
    // Display results with better formatting
    cout << fixed << setprecision(10);
    cout << "\nQuadrature Points (x_k): ";
    for (int i = 0; i < n; i++) {
        cout << xk[n-1][i] << " ";
    }
    cout << "\nWeights (lambda_k): ";
    for (int i = 0; i < n; i++) {
        cout << lambda_k[n-1][i] << " ";
    }
    cout << "\nFinal Integral Value: " << integral << endl;
}

int main() {
    double a, b;
    int n;
    
    cout << "Enter lower limit of integration: ";
    cin >> a;
    cout << "Enter upper limit of integration: ";
    cin >> b;
    cout << "Enter number of quadrature points (1-4): ";
    cin >> n;
    
    gaussLegendreQuadrature(a, b, n);
    
    return 0;
}
