#include <iostream>
#include <iomanip>
using namespace std;
typedef double (*type_f)(double);


double f(double x)
{
    return sin(x) * sin(x) - x / 5;
}

double trapezoid(type_f f, double a, double b, int n)
{
    double s = 0, x, h;
    h = (b - a) / n;
    x = a;
    for (int i = 1; i <= n; i++)
    {
        s += (f(x) + f(x + h)) / 2.0;
        x += h;
    }
    s *= h;
    return s;
}

int main()
{
    double a = 0, b = 4;
    double eps, p, r1, r2;
    int n, n1;
    double s = 0.153;
    //cout << fixed << setprecision(2)
    int code;
    cout << "By a specified number of partitions (n) - 1, by a specified accuracy (eps) - 2\n";
    cin >> code;
    switch (code)
    {
    case 1:
        cout << "n: ";
        cin >> n;
        cout << "Calculation by partitioning n = " << n << endl;
        r1 = trapezoid(f, a, b, n);
        break;
    case 2:
        n1 = 2;
        cout << "eps: ";
        cin >> eps;
        r1 = trapezoid(f, a, b, n1);
        do
        {
            n1 *= 2;
            r2 = trapezoid(f, a, b, n1);
            p = abs(r2 - r1);
            r1 = r2;

        } while (p > eps);
        cout << "Calculation by accuracy eps = " << fixed << eps << endl;
        break;
    }
    cout << "Integral value = " << r1;
}