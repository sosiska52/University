#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>

double function(double x)
{
    return x / (1 + pow(x, 2));
}

using namespace std;
int main()
{
    srand(time(NULL));
    double xbegin , xend , ybegin, yend, N, n = 0;
    double randx, randy, y;
    cout << "Enter borders for X:\n";
    cin >> xbegin >> xend;
    cout << "Enter borders for Y:\n";
    cin >> ybegin >> yend;
    cout << "Enter N:\n";
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        randx = xbegin + (xend - xbegin) * rand() / (double)RAND_MAX;
        randy = ybegin + (yend - ybegin) * rand() / (double)RAND_MAX;
        y = function(randx);
        if (y>=randy)
            n++;
    }
    double sq = (xend - xbegin) * (yend - ybegin);
    double sf = n  / N * sq ;
    cout <<"number of n = " << n << endl;
    cout <<"the area of the figure = " << sf;
}