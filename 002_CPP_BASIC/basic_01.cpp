//#### Aşağıdaki C++ programı derlenip çalıştırıldığında standart çıkış akımına ne yazar?

int foo(int *p, int *q)
{
	*p = 1;
	*q = 2;
	
	return *p + *q;
}

char str[] = "0123";

#include <iostream>

int main()
{
	using namespace std;

	int a = 3;
	int b = 4;
	int c = foo(&a, &a); // c = 4 a = 2
	cout << c; // 4
	(c == a + b ? a : b) = 5; // b = 5;
	cout << a << b; // 25
	int i = 0;
	str[i] = i[str + 2]; // str = "2123"
	cout << str; // 2123
	//cout << "4252123\n";
	
} 


//[ödevin cevabı](https://vimeo.com/443978828)
