#include <stdio.h>

#define N 2
int a;
int *pa = &a;
int exponentiation(int *&a){
	int res = 2;
    for (int i = 1; i < *a; ++i)
    {
    	res = res * N;
    }
    return res;
}
int main ()
{
	printf("Введите число: ");
	scanf("%d",&a);
	printf("Число %d в степени %d = %d\n", N,a,exponentiation(pa));
	return 0;

}