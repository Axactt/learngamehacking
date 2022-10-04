#include<iostream>

struct a
{
	struct b
	{
		int i;
		float j;
	}x;
	struct c
	{
		int k;
		float l;
	}y;
}z;

int main()
{
	struct a* foo = &z;

	printf("%d\n",foo);                  //address of z
	printf("%d\n",&(foo->y));            //address of z.y
	printf("%d\n",&((&(foo->y))->k));  //address of z.y.k


	int offset_k = (char*) &((&(foo->y))->k)-(char*) foo; // casting it to byte pointer
	printf("%d\n",offset_k);

	return 0;
}