#include <iostream>

using namespace std;

double f(double x)
{
    return sin(x) * sin(x) - x / 5;
}

double PNS(double t, int i, double* x, double* y)
{
    return (y[i - 1] + (t - x[i + 1]) * (y[i] - y[i - 1]) / (x[i] - x[i - 1])) + (t - x[i - 1]) * (t - x[i]) * ((y[i - 1] - y[i])  \
     / (x[i - 1] - x[i]) - (y[i] - y[i + 1]) / (x[i] - x[i + 1])) / (x[i - 1] - x[i + 1]);
}

int main()
{
    int i, j;
    double a = 0, b = 4, m = 11, n = 3;
    double x_i[11], y_i[11];
    for (i = 1; i < m + 1; i++)
    {
        x_i[i - 1] = a + (i - 1.0) * (b - a) / (m - 1);
        y_i[i - 1] = f(x_i[i - 1]);
        cout << "x: " << x_i[i - 1] << " y:" << y_i[i - 1] << endl;
    }
    cout << "Approximation" << endl;
    for (j = 1; j < 22; j++)
    {
        double x_j = a + (j - 1) * (b - a) / 20;
        if (x_i[0] <= x_j && x_i[10] >= x_j)
        {
            i = 3;
            while (x_j > x_i[i])
                i++;
            i = i - 1;
        }
        double d = f(x_j) - PNS(x_j, i, x_i, y_i);
        cout << "f: " << f(x_j) << " PNS: " << PNS(x_j, i, x_i, y_i) << " d: " << d << endl;
    }
}