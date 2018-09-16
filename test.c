#include <math.h>
#define C 64
int main ()
{
    double py = 500;
    int n = py / C * C - 1;
    printf("%d\n", n);
}