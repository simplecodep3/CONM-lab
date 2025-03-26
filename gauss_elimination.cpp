
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
bool isDiagonallyDominant(vector<vector<double>>& A, int n) {
    for(int i = 0; i < n; i++) {
        double sum = 0;
        double diag = abs(A[i][i]);
        
        for(int j = 0; j < n; j++) {
            if(i != j) {
                sum += abs(A[i][j]);
            }
        }
        
        if(diag <= sum) {
            return false;
        }
    }
    return true;
}

bool makeDiagonallyDominant(vector<vector<double>>& A, vector<double>& b, int n) {
    for (int i = 0; i < n; ++i) {
        int maxRow = i;
        double maxValue = abs(A[i][i]);
        for (int j = i + 1; j < n; ++j) {
            if (abs(A[j][i]) > maxValue) {
                maxValue = abs(A[j][i]);
                maxRow = j;
            }
        }
        if (maxRow != i) {
            swap(A[i], A[maxRow]);
            swap(b[i], b[maxRow]);
        }
    }
    return isDiagonallyDominant(A, n);
}

int findRank(vector<vector<double>> A, int n, int m) {
    const double EPSILON = 1e-10;
    int rank = 0;
    vector<bool> rowSelected(n, false);

    for(int col = 0; col < m; col++) {
        int row;
        for(row = 0; row < n; row++) {
            if(!rowSelected[row] && abs(A[row][col]) > EPSILON)
                break;
        }

        if(row != n) {
            rank++;
            rowSelected[row] = true;
            for(int i = 0; i < n; i++) {
                if(i != row && abs(A[i][col]) > EPSILON) {
                    double mult = A[i][col] / A[row][col];
                    for(int j = col; j < m; j++)
                        A[i][j] -= mult * A[row][j];
                }
            }
        }
    }
    return rank;
}

bool checkConsistency(vector<vector<double>>& A, vector<double>& b, int n) {
    // Create augmented matrix
    vector<vector<double>> aug(n, vector<double>(n + 1));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            aug[i][j] = A[i][j];
        }
        aug[i][n] = b[i];
    }

    int rankA = findRank(A, n, n);
    int rankAug = findRank(aug, n, n + 1);

    cout<< "Rank of coefficient matrix: " << rankA << endl;
    cout<< "Rank of augmented matrix: " << rankAug << endl;

    return (rankA == rankAug);
}

// Function to perform forward elimination
void displayMatrix(const vector<vector<double>>& matrix, const vector<double>& rhs, const string& title) {
    cout << "\n" << title << ":\n";
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << fixed << setprecision(4) << matrix[i][j] << " ";
        }
        cout << "| " << setw(10) << rhs[i] << endl;
    }
    cout << endl;
}
void forwardElimination(vector<vector<double>>& matrix, vector<double>& rhs, int n) {
    for (int k = 0; k < n; ++k) {
        // Find the pivot element
        int maxRow = k;
        for (int i = k + 1; i < n; ++i) {
            if (fabs(matrix[i][k]) > fabs(matrix[maxRow][k])) {
                maxRow = i;
            }
        }

        // Swap the rows
        swap(matrix[k], matrix[maxRow]);
        swap(rhs[k], rhs[maxRow]);

        // Make the elements below the pivot element zero
        for (int i = k + 1; i < n; ++i) {
            double factor = matrix[i][k] / matrix[k][k];
            for (int j = k; j < n; ++j) {
                matrix[i][j] -= factor * matrix[k][j];
            }
            rhs[i] -= factor * rhs[k];
        }
    }
}

// Function to perform back substitution
vector<double> backSubstitution(const vector<vector<double>>& matrix, const vector<double>& rhs, int n) {
    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = rhs[i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= matrix[i][j] * x[j];
        }
        x[i] /= matrix[i][i];
    }
    return x;
}

// Function to perform Gauss elimination
vector<double> gaussElimination(vector<vector<double>>& matrix, vector<double>& rhs, int n) {
    forwardElimination(matrix, rhs, n);
    cout<<"After Forward Elimination"<<endl;
    displayMatrix(matrix, rhs, "Augmented Matrix");
    return backSubstitution(matrix, rhs, n);
}

// Main Function
int main() {
    int n;
    cout << "Enter the number of equations: ";
    cin >> n;

    vector<vector<double>> matrix(n, vector<double>(n));
    vector<double> rhs(n);

    cout << "Enter the coefficients of the matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << "Enter the right-hand side values:\n";
    for (int i = 0; i < n; ++i) {
        cin >> rhs[i];
    }

    if (!checkConsistency(matrix, rhs, n)) {
        cout << "The system is inconsistent. No solution exists.\n";
        return 1;
    }

    if (isDiagonallyDominant(matrix, n)) {
        cout << "The matrix is diagonally dominant. Solving the system...\n";
        vector<double> solution = gaussElimination(matrix, rhs, n);
        cout << "Final Solution:\n";
        for (int i = 0; i < n; ++i) {
            cout << "x[" << i << "] = " << fixed << setprecision(6) << solution[i] << endl;
        }
    } else {
        cout << "The matrix is not diagonally dominant. Attempting to convert it...\n";
        if (makeDiagonallyDominant(matrix, rhs,n)) {
            cout << "The matrix has been converted to a diagonally dominant matrix. The augmented matrix is:\n";
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    cout << setw(10) << matrix[i][j] << " ";
                }
                cout << "| " << rhs[i] << endl;
            }
            vector<double> solution = gaussElimination(matrix, rhs, n);
            cout << "Final Solution:\n";
            for (int i = 0; i < n; ++i) {
                cout << "x[" << i << "] = " << fixed << setprecision(6) << solution[i] << endl;
            }
        } else {
            cout << "The matrix cannot be converted to a diagonally dominant matrix. The Gauss-Seidel method is not applicable.\n";
        }
    }

    return 0;
}