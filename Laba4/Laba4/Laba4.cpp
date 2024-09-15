#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

using namespace std;

struct Deque
{
    Deque* prev, * next;
    int info;
};


void Create_random(Deque** e, Deque** p, int len)
{
    for (int i = 0; i < len; i++)
    {
        int in = (rand() % 100 + 1);
        Deque* t = new Deque;
        t->info = in;
        t->next = t->prev = NULL;
        if (i == 0)
            *p = *e = t;
        else
        {
            (*e)->next = t;
            t->next = NULL;
            t->prev = *e;
            *e = t;
        }
    }
}

void Create_manual(Deque** e, Deque** p, int len)
{
    for (int i = 0; i < len; i++)
    {
        int in;
        cin >> in;
        Deque* t = new Deque;
        t->info = in;
        t->next = t->prev = NULL;
        if (i == 0)
            *p = *e = t;
        else
        {
            (*e)->next = t;
            t->next = NULL;
            t->prev = *e;
            *e = t;
        }
    }
}

Deque* add_to_beg(int info, Deque* p)
{

    Deque* t = new Deque;
    t->info = info;
    t->prev = NULL;
    t->next = p;
    if (p != NULL) p->prev = t;
    return t;
}

Deque* add_to_end(int info, Deque* e)
{
    Deque* t = new Deque;
    t->info = info;
    t->next = NULL;
    t->prev = e;
    if (e != NULL) e->next = t;
    return t;
}

void view_from_beg(Deque* p)
{
    while (p != NULL)
    {
        cout << p->info << endl;
        p = p->next;
    }
}

void view_from_end(Deque* e)
{
    while (e != NULL)
    {
        cout << e->info << endl;
        e = e->prev;
    }
}

int _min(Deque* p)
{
    int Min = p->info;
    while (p != NULL)
    {
        Min = min(Min, p->info);
        p = p->next;
    }
    return Min;
}


void Del_All(Deque* p)
{
    while (p != NULL) {
        Deque* t = p;
        p = p->next;
        delete t;
    }
}

int main()
{
    srand(time(NULL));
    char code, bcode;
    int len, i;
    Deque* beg = NULL, * e = NULL;
    while (true)
    {
        cout << "Create - 1\nAdd - 2\nView - 3\nTask - 4\nEXIT - 0" << endl;
        cin >> code;
        switch (code)
        {
        case '1':
            if (beg != NULL) {
                cout << "Memory Free!" << endl;
                Del_All(beg);
                beg = e = NULL;
                break;
            }
            cout << "random - 1\nmanual - 2" << endl;
            cin >> bcode;
            cout << "Input a length: ";
            cin >> len;
            switch (bcode) {
            case '1':
                Create_random(&e, &beg, len);
                break;
            case '2':
                cout << "Input elements\n";
                Create_manual(&e, &beg, len);
                break;
            }
            break;
        case '2':
            cout << "Input a length: ";
            cin >> len;
            cout << "To begin - 1\nTo end - 2" << endl;
            cin >> bcode;
            for (i = 0; i < len; i++)
            {
                int in = (rand() % 100 + 1);
                switch (bcode)
                {
                case '1':
                    beg = add_to_beg(in, beg);
                    break;
                case '2':
                    e = add_to_end(in, e);
                    break;
                }
            }

            break;
        case '3':
            cout << "From begin - 1\nFrom end - 2" << endl;
            cin >> bcode;
            switch (bcode)
            {
            case '1':
                view_from_beg(beg);
                break;
            case '2':
                view_from_end(e);
                break;
            }
            break;
        case '4':
        {
            if (beg == NULL)
            {
                cout << "The Deque is empty!\n";
                break;
            }
            int Min = _min(beg);
            Deque* _beg= NULL,* t = beg;
            if (t->info == Min)
                cout << "Deque's begin is a minimum\n";
            else
            {
                while (t != NULL) {
                    if (t->info == Min)
                        break;
                    _beg = add_to_beg(t->info, _beg);
                    t = t->next;
                }


                view_from_beg(_beg);
            }
            Deque* _e = NULL;
            t = e;
            cout << "\n\n";
            if (t->info == Min)
                cout << "Deque's end is a minimum\n";
            else
            {
                while (t != NULL) {
                    if (t->info == Min)
                        break;
                    _e = add_to_end(t->info, _e);
                    t = t->prev;
                }

                view_from_end(_e);
            }
            break;
        }
        case '0':
            if (beg != NULL)
                Del_All(beg);
            return 0;

        }
    }
}