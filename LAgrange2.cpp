#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void printTermWithFraction(double coeff, int power, bool isFirst, double denom) {
    // Handle signs properly
    bool isNegative = (coeff * denom < 0);  // True if result is negative
    double absCoeff = abs(coeff);
    double absDenom = abs(denom);

    // Print sign
    if(!isFirst && !isNegative) {
        cout << "+ ";
    }
    if(isNegative) {
        cout << "- ";
    }
    
    // Print coefficient
    if(absCoeff == absDenom) {
        cout << "1";
    } else {
        cout << absCoeff;
        if(absDenom != 1) {
            cout << "/" << absDenom;
        }
    }
    
    // Print variable and power
    if(power > 0) {
        cout << "x";
        if(power > 1) {
            cout << "^" << power;
        }
    }
    cout << " ";
}

vector<double> multiplyPolynomials(const vector<double>& p1, const vector<double>& p2) {
    vector<double> result(p1.size() + p2.size() - 1, 0);
    for(int i = 0; i < p1.size(); i++) {
        for(int j = 0; j < p2.size(); j++) {
            result[i + j] += p1[i] * p2[j];
        }
    }
    return result;
}

void printPolynomial(const vector<double>& coeffs, double denom) {
    bool first = true;
    bool anyTermPrinted = false;
    
    for(int i = coeffs.size()-1; i >= 0; i--) {
        if(abs(coeffs[i]) > 1e-13) {
            printTermWithFraction(coeffs[i], i, first, denom);
            first = false;
            anyTermPrinted = true;
        }
    }
    
    if(!anyTermPrinted) {
        cout << "0";
    }
    cout << endl;
}

// New function to evaluate polynomial at a point
double evaluatePolynomial(const vector<double>& coeffs, double x) {
    double result = 0.0;
    double power = 1.0;
    for(int i = 0; i < coeffs.size(); i++) {
        result += coeffs[i] * power;
        power *= x;
    }
    return result;
}

int main() {
    int n;
    cout << "Enter number of data points: ";
    cin >> n;
    
    vector<double> x(n), y(n);
    
    cout << "Enter x values:\n";
    for(int i = 0; i < n; i++) {
        cin >> x[i];
    }
    
    cout << "Enter y values:\n";
    for(int i = 0; i < n; i++) {
        cin >> y[i];
    }
    
    // Calculate Lagrange basis polynomials
    vector<vector<double>> terms;
    vector<double> denominators(n, 1.0);
    cout << "\nLagrange basis polynomials:\n";
    
    for(int i = 0; i < n; i++) {
        vector<double> Li = {1.0};  // Start with constant term 1
        double denom = 1.0;
        
        for(int j = 0; j < n; j++) {
            if(j != i) {
                // Create term (x - xj)
                vector<double> term = {-x[j], 1.0};
                
                // Multiply current Li by (x - xj)
                Li = multiplyPolynomials(Li, term);
                
                // Accumulate denominator
                denom *= (x[i] - x[j]);
            }
        }
        
        cout << "L" << i << "(x) = ";
        printPolynomial(Li, denom);
        terms.push_back(Li);
        denominators[i] = denom;
    }
    
    // Calculate final interpolation polynomial
    vector<double> result(terms[0].size(), 0.0);
    
    // Calculate the final polynomial
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < terms[i].size(); j++) {
            result[j] += (terms[i][j] * y[i]) / denominators[i];
        }
    }
    
    cout << "\nInterpolation polynomial f(x) = ";
    printPolynomial(result, 1.0);
    
    // Evaluate polynomial at points
    char choice;
    do {
        double evalPoint;
        cout << "\nEnter x value to evaluate polynomial at: ";
        cin >> evalPoint;
        
        double value = evaluatePolynomial(result, evalPoint);
        cout << "f(" << evalPoint << ") = " << value << endl;
        
        cout << "Do you want to evaluate at another point? (y/n): ";
        cin >> choice;
    } while(choice == 'y' || choice == 'Y');
    
    return 0;
}