#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

using namespace std;

struct Stack
{
    int info;
    Stack* next;
};

Stack* pb(int info, Stack* p)
{
    Stack* t = new Stack;
    t->info = info;
    t->next = p;
    return t;
}

void view(Stack* p)
{
    while (p != NULL) {
        cout << p->info << endl;
        p = p->next;
    };
}

void Del_All(Stack* p)
{
    while (p != NULL) {
        Stack* t = p;
        p = p->next;
        delete t;
    };
}

int _Min(Stack* p)
{
    int Min = p->info;
    while (p != NULL) {
        Min = min(Min, p->info);
        p = p->next;
    }
    return Min;
}

int main()
{
    char code, bcode;
    int len, i, in;
    Stack* beg = NULL;
    srand(time(NULL));

    while (true) {
        cout << "Create - 1\nAdd - 2\nView - 3\nTask - 4\nEXIT - 0" << endl;
        cin >> code;
        switch (code)
        {
        case '1':
            if (beg != NULL) {
                cout << "Memory Free!" << endl;
                Del_All(beg);
                beg = NULL;
                break;
            }
            cout << "random - 1\nmanual - 2" << endl;
            cin >> bcode;
            cout << "Input a length: ";
            cin >> len;

            switch (bcode) {
            case '1':
                for (i = 0; i < len; i++)
                {
                    in = (rand() % 100 + 1);
                    beg = pb(in, beg);
                }
                break;
            case '2':
                cout << "Input elements\n";
                for (i = 0; i < len; i++)
                {
                    cin >> in;
                    beg = pb(in, beg);
                }
                break;
            }
            break;
        case '2':
            cout << "Input a length: ";
            cin >> len;
            cout << "Input elements" << endl;
            for (i = 0; i < len; i++)
            {
                cin >> in;
                beg = pb(in, beg);
            }
            break;
        case '3':
            if (beg == NULL)
            {
                cout << "Stack is empty!" << endl;
                break;
            }
            view(beg);
            break;
        case '4':
        {
            if (beg == NULL)
            {
                cout << "Stack is empty!" << endl;
                break;
            }
            int Min = _Min(beg);
            Stack* _begin = beg;
            Stack* res = NULL;
            if (beg->info == Min)
            {
                cout << "Stack's top is a minimum\n";
                break;
            }
            while (_begin != NULL) {
                if (_begin->info == Min)
                    break;
                res = pb(_begin->info, res);
                _begin = _begin->next;
            }
            view(res);
        }
        break;
        case '0':
            if (beg != NULL)
                Del_All(beg);
            return 0;

        }
    }
}