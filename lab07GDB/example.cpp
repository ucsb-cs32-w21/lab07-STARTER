#include <stdio.h>

class example {
public:
   int a;
   float b;
   int c;
   class example * other;
};

void kerblam(int *p)
{
   *p = 0;
}

void explode()
{
   kerblam(NULL);
}

void kaboom()
{
   explode();
}

int main(void)
{
   example ex = {1, 2.0f, 3, NULL};
   example ex2 = {2, 3.0f, 4, NULL};
   example * exp = &ex2;
   ex2.other = &ex;

   printf("%d\n", exp->a);

   /* bad program is about to die */
   kaboom();

   return 0;
}
