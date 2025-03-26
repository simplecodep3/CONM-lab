#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

// Predefined function option
double f(double x) {
    return 1 / (1 + x); // Corrected function: f(x) = 1 / (1 + x)
    // Can be modified based on requirement
}

class NumericalIntegration {
private:
    vector<double> x_values;
    vector<double> fx_values;
    bool useTabulated;
    
    // Get function value (either from predefined function or tabulated data)
    double getValue(double x) {
        if (!useTabulated) {
            return f(x);
        }
        
        // For tabulated data, use linear interpolation
        for (size_t i = 0; i < x_values.size() - 1; i++) {
            if (x >= x_values[i] && x <= x_values[i + 1]) {
                double ratio = (x - x_values[i]) / (x_values[i + 1] - x_values[i]);
                return fx_values[i] + ratio * (fx_values[i + 1] - fx_values[i]);
            }
        }
        return 0;
    }

public:
    NumericalIntegration() : useTabulated(false) {}
    
    // Initialize with tabulated data
    void setTabulatedData() {
        useTabulated = true;
        cout << "Enter number of points: ";
        int n;
        cin >> n;
        
        x_values.resize(n);
        fx_values.resize(n);
        
        cout << "Enter x and f(x) values (one pair per line):\n";
        for (int i = 0; i < n; i++) {
            cin >> x_values[i] >> fx_values[i];
        }
    }
    
    // Trapezoidal Rule
    double trapezoidalRule(double a, double b, int n) {
        double h = (b - a) / n;
        double sum = getValue(a) + getValue(b);
        
        for (int i = 1; i < n; i++) {
            sum += 2 * getValue(a + i * h);
        }
        
        return (h / 2) * sum;
    }
    
    // Simpson's 1/3 Rule
    double simpsons13Rule(double a, double b, int n) {
        if (n % 2 != 0) n++; // Ensure n is even
        double h = (b - a) / n;
        double sum = getValue(a) + getValue(b);
        
        for (int i = 1; i < n; i++) {
            sum += (i % 2 == 0) ? 2 * getValue(a + i * h) : 4 * getValue(a + i * h);
        }
        
        return (h / 3) * sum;
    }
    
    // Simpson's 3/8 Rule
    double simpsons38Rule(double a, double b, int n) {
        if (n % 3 != 0) n += (3 - n % 3); // Ensure n is multiple of 3
        double h = (b - a) / n;
        double sum = getValue(a) + getValue(b);
        
        for (int i = 1; i < n; i++) {
            sum += (i % 3 == 0) ? 2 * getValue(a + i * h) : 3 * getValue(a + i * h);
        }
        
        return (3 * h / 8) * sum;
    }
};

int main() {
    NumericalIntegration integrator;
    int choice;
    double a, b, stepSize;
    
    cout << "Choose input type:\n";
    cout << "1. Use predefined function\n";
    cout << "2. Enter tabulated data\n";
    cout << "Enter choice (1-2): ";
    cin >> choice;
    
    if (choice == 2) {
        integrator.setTabulatedData();
    }
    
    cout << "Enter lower limit (a): ";
    cin >> a;
    cout << "Enter upper limit (b): ";
    cin >> b;
    cout << "Enter step size: ";
    cin >> stepSize;
    
    int n = (b - a) / stepSize; // Calculate number of intervals
    cout << fixed << setprecision(6);
    
    cout << "\nSelect integration method:\n";
    cout << "1. Trapezoidal Rule\n";
    cout << "2. Simpson's 1/3 Rule\n";
    cout << "3. Simpson's 3/8 Rule\n";
    cout << "4. Compare all methods\n";
    cout << "Enter choice (1-4): ";
    cin >> choice;
    
    switch (choice) {
        case 1:
            cout << "\nTrapezoidal Rule Result: " 
                 << integrator.trapezoidalRule(a, b, n)
                 << "\nStep size: " << stepSize << endl;
            break;
            
        case 2:
            cout << "\nSimpson's 1/3 Rule Result: " 
                 << integrator.simpsons13Rule(a, b, n)
                 << "\nStep size: " << stepSize << endl;
            break;
            
        case 3:
            cout << "\nSimpson's 3/8 Rule Result: " 
                 << integrator.simpsons38Rule(a, b, n)
                 << "\nStep size: " << stepSize << endl;
            break;
            
        case 4:
            cout << "\nComparison of Methods:\n";
            cout << "----------------------------------------\n";
            cout << "Method            | Result    | Step Size\n";
            cout << "----------------------------------------\n";
            cout << "Trapezoidal Rule  | " << integrator.trapezoidalRule(a, b, n) 
                 << " | " << stepSize << endl;
            cout << "Simpson's 1/3 Rule| " << integrator.simpsons13Rule(a, b, n) 
                 << " | " << stepSize << endl;
            cout << "Simpson's 3/8 Rule| " << integrator.simpsons38Rule(a, b, n) 
                 << " | " << stepSize << endl;
            cout << "----------------------------------------\n";
            break;
            
        default:
            cout << "Invalid choice!\n";
    }
    
    return 0;
}