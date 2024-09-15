#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#define pb push_back
//#ifndef __cpp_lib_string_contains
//#error "The standard library doesn't support std::string::contains()."
//#endif

using namespace std;

struct Stack
{
    char info;
    Stack* next;
};

Stack* push_back(char info, Stack* p)
{
    Stack* t = new Stack;
    t->info = info;
    t->next = p;
    return t;
}

char Out(Stack** p)
{
    Stack* t = (*p)->next;
    char info = (*p)->info;
    delete* p;
    *p = t;
    return info;

}

int Prior(char a)
{
    switch (a)
    {
    case '^': return 4;
    case '*': case '/': return 3;
    case '-': case '+': return 2;
    case '(': return 1;
    }
    return 0;
}

void Del_All(Stack* p)
{
    while (p != NULL) {
        Stack* t = p;
        p = p->next;
        delete t;
    };
}

double Result(string PRN, double a = 8.5, double b = 0.3, double c = 2.4, double d = 7.9, double e = 1.6)
{
    char ch, ch1, ch2, chr = 'z' + 1;
    double op1, op2, res = 0; 
    double mas[201];
    mas[int('a')] = a;
    mas[int('b')] = b;
    mas[int('c')] = c;
    mas[int('d')] = d;
    mas[int('e')] = e;
    Stack* t = new Stack;
    int i, len = PRN.length();
    for (i = 0; i < len; i++)
    {
        ch = PRN[i];
        if (ch != '+' && ch != '-' && ch != '/' && ch != '*') t = pb(ch, t);
        else
        {

            ch1 = Out(&t);
            ch2 = Out(&t);
            op1 = mas[int(ch1)];
            op2 = mas[int(ch2)];

            switch (ch)
            {
            case '+': res = op2 + op1; break;
            case '-': res = op2 - op1; break;
            case '*': res = op2 * op1; break;
            case '/': res = op2 / op1; break;
            case '^': res = pow(op2, op1); break;
            }
            mas[chr] = res;
            t = pb(chr, t);
            chr++;
        }
    }
    return res;
}

int main()
{
    Stack* opt = NULL;
    string ss, str;
    int code, i, len;
    double a, b, c, d, e;
    while (true)
    {
        cout << "Example - 1, Input - 2, Exit - 0: ";
        cin >> code;
        switch (code)
        {
        case 1:
            str = "a/(b*(c+d))-e";
            i, len = str.length();
            for (i = 0; i < len; i++)
            {
                if (str[i] >= 'a' && str[i] <= 'z') ss += str[i];
                else
                {
                    if (str[i] == '(')opt = pb(str[i], opt);
                    else if (str[i] == ')')
                    {
                        while (opt->info != '(')
                            ss += Out(&opt);
                        Out(&opt);
                    }
                    else
                    {
                        while (opt != NULL && Prior(opt->info) >= Prior(str[i]))
                            ss += Out(&opt);
                        opt = pb(str[i], opt);
                    }
                }
            }
            while (opt != NULL)
                ss += Out(&opt);
            std::cout << fixed << setprecision(3);
            cout << Result(ss) << endl;
            Del_All(opt);
            break;
        case 2:
            cin >> str;
            cout << "a: ";
            cin >> a;
            cout << "b: ";
            cin >> b;
            cout << "c: ";
            cin >> c;
            cout << "d: ";
            cin >> d;
            cout << "e: ";
            cin >> e;
             i, len = str.length();
            for (i = 0; i < len; i++)
            {
                if (str[i] >= 'a' && str[i] <= 'z') ss += str[i];
                else
                {
                    if (str[i] == '(')opt = pb(str[i], opt);
                    else if (str[i] == ')')
                    {
                        while (opt->info != '(')
                            ss += Out(&opt);
                        Out(&opt);
                    }
                    else
                    {
                        while (opt != NULL && Prior(opt->info) >= Prior(str[i]))
                            ss += Out(&opt);
                        opt = pb(str[i], opt);
                    }
                }
            }
            while (opt != NULL)
                ss += Out(&opt);
            std::cout << fixed << setprecision(3);
            cout << Result(ss, a, b, c, d, e) << endl;
            Del_All(opt);
            break;
        case 0:
            return 0;
        }
    }
}