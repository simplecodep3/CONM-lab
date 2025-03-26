#include <iostream>
#include <vector>
#include <iomanip>
#include<algorithm>
#include <math.h>
using namespace std;

void gaussianElimination(vector<vector<double>>& matrix, vector<double>& result) {
    int n = matrix.size();

    for (int i = 0; i < n; i++) {
        // Partial Pivoting
        for (int k = i + 1; k < n; k++) {
            if (fabs(matrix[i][i]) < fabs(matrix[k][i])) {
                for (int j = 0; j <= n; j++) {
                    swap(matrix[i][j], matrix[k][j]);
                }
            }
        }

        // Forward Elimination
        for (int k = i + 1; k < n; k++) {
            double t = matrix[k][i] / matrix[i][i];
            for (int j = 0; j <= n; j++) {
                matrix[k][j] = matrix[k][j] - t * matrix[i][j];
            }
        }
    }

    // Back Substitution
    for (int i = n - 1; i >= 0; i--) {
        result[i] = matrix[i][n];
        for (int j = i + 1; j < n; j++) {
            result[i] = result[i] - matrix[i][j] * result[j];
        }
        result[i] = result[i] / matrix[i][i];
    }
}

int main() {
    int n;
    cout << "Enter the number of variables: ";
    cin >> n;

    vector<vector<double>> matrix(n, vector<double>(n + 1));
    vector<double> result(n);

    cout << "Enter the augmented matrix coefficients row-wise:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cin >> matrix[i][j];
        }
    }

    gaussianElimination(matrix, result);

    cout << "The solution is: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << fixed << setprecision(6) << result[i] << endl;
    }

    return 0;
}