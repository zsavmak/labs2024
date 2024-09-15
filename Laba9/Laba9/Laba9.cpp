#include <iostream>
#include <cmath>
using namespace std;


double f(double x) {
    return sin(x) * sin(x) - x / 5.0 - 1;
}

double f_prime(double x) {
    return 2 * sin(x) * cos(x) - 1 / 5.0;
}

double f_double_prime(double x) {
    return 2 * cos(2 * x);
}

double find_initial_approximation(double a, double b, double tol = 1e-6) {
    double x = a;
    while (x <= b) {
        double fpx = f_prime(x);
        double fppx = f_double_prime(x);

        if (fabs(fpx) > tol && fabs(2 * f(x) * fppx / (fpx * fpx)) < 1) {
            return x;
        }
        x += (b - a) / 100;
    }
    return (a + b) / 2;
}

double newton_method(double x, double tol, int max_iter) {
    double x_new;
    int iter = 0;

    while (iter < max_iter) {
        double fx = f(x);
        double fpx = f_prime(x);

        if (fabs(fpx) <= tol) {
            return x;
        }

        x_new = x - fx / fpx;
        if (fabs(x - x_new) < tol) {
            return x_new;  
        }

        x = x_new;
        iter++;
    }
    return x; 
}

bool is_root_near(double x, double root, double tol) {
    return fabs(x - root) < tol;
}

int main() {
    double a = -4.0, b = 0.0;
    double tol = 0.001;
    int max_iter = 100;
    double step = (b - a) / 100;
    double x = a, root, root0;
    bool first = true;

    while (x <= b) {
        x = find_initial_approximation(x, b);
        root = newton_method(x, tol, max_iter);
        if (first)
        {
            if (is_root_near(root, x, 0.1)) {
                cout << "Root found: " << root << endl;
                root0 = root;
                first = false;
            }
        }
        else
        {
            if (is_root_near(root, x, 0.1) &&! is_root_near(root0,root, tol)) {
                cout << "Root found: " << root << endl;
                root0 = root;
            }
        }
        x += step;
    }
    return 0;
}
