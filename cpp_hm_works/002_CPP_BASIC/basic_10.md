// #### Aşağıdaki kodda yapılan bildirimlerde ve atama işlemlerinde gereken her yerde  uygun tür dönüştürme(type-cast) operatörünü kullanınız:

#include <cstdlib>

enum class Color {Red, Blue, Green, Black};
enum class Pos{Off, On, Hold, Standby};

struct Data {
	int a, b, c;
};

int main()
{
	Color c{ Color::Blue };
	Pos pos{ Pos::Hold};
	int ival = 2;
	double dval{ 3.862 };
	Data data{ 1, 3, 5 };
	const double *dptr{ &dval };

	int *ptr = static_cast<int*> (std::malloc(100'000));
	int x = c; // enum class --> int ? 
	pos = c; // enum class --> enum class ? 
	c = ival; // int to enum class ? 
	ival = dval; // true.  c++ convert double type  to int type implicitly.
	const int *cptr = &ival;
	int *iptr = cptr; // const int * --> int * ? 
	char *cp = "Necati Ergin"; // true 
	char *ps = &dval; // double --> char * dl
	int *ip = &data;
	char *dp = dptr;
	dval = ival;
	void *vptr = &ival;
	vptr = &vptr;
	float f = dval;
}
