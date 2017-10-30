// where_are_the_bits.c ... determine bit-field order
// COMP1521 Lab 03 Exercise
// Written by ...

#include <stdio.h>
#include <stdlib.h>

struct _bit_fields {
   unsigned int a : 4,
                b : 8,
                c : 20;
};

int main(void)
{
   struct _bit_fields x;

   printf("%ul\n",sizeof(x));
   
   x.a = 0x00003;
   printf("%x\n", x.a);
   printf("%x\n", x.b); 
   printf("%x\n", x.c); 
   return 0;
}
