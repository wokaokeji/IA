/*求: (a*b)%m, a*b可能溢出*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

#define MAX_WHILE 10000000
#define MAX_NUM (1<<15)


#define MASK (1 << (8 * sizeof(unsigned int) - 1))

unsigned int mulmod(unsigned int a, unsigned int b, unsigned int c);

int main()
{
    int it = 0;
    srand(time(NULL));
    while(it++ < MAX_WHILE)
    {

        unsigned int ret,
                     a = rand() % MAX_NUM,
                     b = rand() % MAX_NUM,
                     m = rand() % MAX_NUM + 1;
        ret = mulmod(a, b, m);

        assert(ret == (a * b)%m);
    }
    return 0;
}


unsigned int mulmod(unsigned int a, unsigned int b, unsigned int m)
{
    a %= m;
    b %= m; 

    //printf("a=%u,b=%u, m=%u\n", a, b, m);    
    unsigned int d = 0, c = 0;
    unsigned int mask = MASK;
    while (mask)
    {
        /*invarant: d = (a*c) % m */
        c <<= 1;//c用来验证循环不变式，无实际作用
        d = (d<<1) % m;

        if(0 != (b & mask))
        {
            ++c;
            d = (d + a) % m;
        }

        mask >>= 1;
    }

    assert(b == c);

    //printf("c=%u\n", c);
    return d;
}
