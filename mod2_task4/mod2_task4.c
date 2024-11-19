#include <stdio.h>
#include <stdalign.h>

struct 
{
	char Gender;
	alignas(32) char Adress [32];
	alignas(8) char Name [8];
	alignas(16) char Status [16];
	int Age;
	alignas(16) char Surname [16];
	int GPA;

	

} Person;

struct 
{

	alignas(32) char Adress [32];
	alignas(16) char Status [16];
	alignas(16) char Surname [16];
	alignas(8) char Name [8];
	char Gender;
	int Age;
	int GPA;

} CompressedPerson;


int main(){


	printf("sizeof Person - %ld\n", sizeof(Person));
	printf("alignof Person - %ld\n", alignof(Person));
	printf("sizeof CompressedPerson - %ld\n", sizeof(CompressedPerson));
	printf("alignof CompressedPerson - %ld\n", alignof(CompressedPerson));



	return 0;
}