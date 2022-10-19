
/*
#### Aşağıdaki kaynak koddaki her bir sentaks hatasını

+ C dilinin kurallarına göre
+ C++ dilinin kurallarına 

#### belirleyiniz. Her bir sentaks hatasının nedenini açıklayınız:
kodun orjinal hali https://github.com/necatiergin/cpp_odev/blob/main/001_C_CPP_FARKLAR/cp_01.md

Odevi Cozen:
Selman Tercioglu
@selmantercioglu
*/


#include <iostream>
#include <stdlib.h>

enum Color {Blue, Red, Yellow};
enum Fruit { Apple, Melon, Mango};

int foo(int, int);
int func(){return 0;}

double sum(int a, int b)
{
	return a + b;
}

int f(int x, int)
{
	return x * x;
}

int g1 = func();
const int g2{};

int main()
{
	const int ci1{};
    std::cout << ci1;
	const int ci2 = func();
	const int c3 = 123;
	char p1[] = "necati";
	int i1 = 12.5;
	int i2 = Red;

	// enum Color color1 = 2;
	// enum Color color2 = 19;
	// enum Color color3 = Mango;
    /*yukaridakilerin hatali olmasinin sebebi c++'da int turunden 
    enum turune implicit donusum olmamasidir..*/
  
	char str[4] = "ali";
	enum Color color = Red;
	// ++color;
	Fruit f = Mango;
	const int cx = 10;
	int ival = 56;
	func();
	const int *ptr = &cx;
	int *cptr = &ival;
	const int *p2 = &ival;
	int *p3 = (int*)malloc(10 * sizeof(int));
	int *p4 = 0;
	int *p5 = NULL;
}

// [ödevin cevabı](https://vimeo.com/432166297)