#include <iostream>
#include <iomanip>
using namespace std;

// Define the differential equation dy/dx = f(x, y)
double f(double x, double y) {
    return 1+ y*y;  // Example: dy/dx = x + y
}

// Euler Method
double euler(double x0, double y0, double h, int steps) {
    double x = x0, y = y0;
    cout << "\nEuler Method:\n";
    cout << "n\t\tx\t\t y" << endl;
    for (int i = 0; i < steps; i++) {
        y = y + h * f(x, y);
        x = x + h;
        cout <<i+1<< "\t\t"<<fixed << setprecision(5) << x << "\t \t" << y << endl;
    }
    return y;
}

// Modified Euler Method
double modified_euler(double x0, double y0, double h, int steps) {
    double x = x0, y = y0;
    cout << "\nModified Euler Method:\n";
    cout << "n\t\tx\t\t y" << endl;
    for (int i = 0; i < steps; i++) {
        double y_predictor = y + h * f(x, y);
        double y_corrector = y + (h / 2) * (f(x, y) + f(x + h, y_predictor));
        y = y_corrector;
        x = x + h;
        cout <<i+1<< "\t\t"<< fixed << setprecision(5) << x << "\t " << y << endl;
    }
    return y;
}

// Comparison of both methods
void compare_methods(double x0, double y0, double h, int steps) {
    double x = x0, y_euler = y0, y_mod_euler = y0;
    cout << "\nComparison of Euler and Modified Euler Methods:\n";
    cout << "n\t\tx\t\t Euler\t \tModified Euler" << endl;
    for (int i = 0; i < steps; i++) {
        y_euler = y_euler + h * f(x, y_euler);
        double y_predictor = y_mod_euler + h * f(x, y_mod_euler);
        double y_corrector = y_mod_euler + (h / 2) * (f(x, y_mod_euler) + f(x + h, y_predictor));
        y_mod_euler = y_corrector;
        x = x + h;
        cout <<i+1<< "\t\t"<< fixed << setprecision(5) << x << "\t\t " << y_euler << "\t " << y_mod_euler << endl;
    }
}

int main() {
    double x0, y0, h;
    int steps, choice;
    
    cout << "Enter initial value of x (x0): ";
    cin >> x0;
    cout << "Enter initial value of y (y0): ";
    cin >> y0;
    cout << "Enter step size (h): ";
    cin >> h;
    cout << "Enter number of steps: ";
    cin >> steps;
    
    do {
        cout << "\nChoose an option:";
        cout << "\n1. Euler method";
        cout << "\n2. Modified Euler method";
        cout << "\n3. Compare both methods";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                euler(x0, y0, h, steps);
                break;
            case 2:
                modified_euler(x0, y0, h, steps);
                break;
            case 3:
                compare_methods(x0, y0, h, steps);
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);
    
    return 0;
}
