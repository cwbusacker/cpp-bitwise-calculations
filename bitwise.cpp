

#include <math.h>
#include <iostream>
using namespace std;
long multiply(long a, long b);
long add(long a, long b);

long long square(unsigned long long num)
{
    if(num == 1)
        return 1;

    //divide by 2;
    long long half = num >> 1;

    if(num & 1)
    {
        return (square(half) << 2) + (half << 2) + 1; 
    }
    else
    {
        return square(half) << 2;
    }


}

long bitAbs(long b)
{
    long long bMask = b >> 31;
    return add(b, bMask) ^ bMask;
}

void quadraticFormula(long long a, long long b, long long c, long long & x1, long long & x2)
{
    // |b|
    long long bMask = b >> 31;
    unsigned long long absB = (b + bMask)^bMask;
    long long bSquare = square(absB); 

    x1 = (~b + 1 + sqrt(bSquare-(multiply(a, c << 2))))/(a << 1);
    x2 = (~b + 1 - sqrt(bSquare-(multiply(a, c << 2))))/(a << 1);
}

long subtract(long a, long b)
{
    if(b == 0)
        return a;

    return subtract(a^b, (~a & b) << 1);

}

long add(long a, long b)
{
    if(b == 0)
        return a;

    return add(a^b, (a & b) << 1);
}

long multiply(long a, long b)
{
    //if a is not odd
    long count = 0, result = 0, temp;
    if(b < a)
    {
        temp = b;
        b = a;
        a = temp;
    }

    if(a >> 31 && b >> 31) //if a and b are negative
    {
        a = bitAbs(a);
        b = bitAbs(b);
    }

    while(b)
    {
        if(b & 1)
        {
            result = add(result, a);
        }

        b >>= 1; //divide b by 2
        a <<= 1; //multiply a by 2

    }

    return result;
}



int main()
{
  cout << "100 - 14 = " << subtract(100, -14) << endl;
  cout << "45 + 43 = " << add(45, 43) << endl;
  cout << "15 x 25 = " << multiply(45,-15) << endl;
  long long x1, x2;
  quadraticFormula(1, -4, 3, x1, x2);
  cout << "x^2 - 4x + 3, y = 0 when x = " << x1 << " OR " << x2 << endl;
}