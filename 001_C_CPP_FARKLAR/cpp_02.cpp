/*
#### Aşağıdaki kod hakkında yorum yapmanız isteniyor:
*/

#include <stdio.h>

int nec = 0;

int main()
{
	struct nec {
		char str[64];
	};
	printf("sizeof(nec) = %zu\n", sizeof(nec));
}

/*
* C++ dillerine gore maskeleme islemi gerceklesecektir.
* Bu nedenle ekrana 64 degeri basilir.
* C programlamada ise nec degiskeni namelookup ta main icerisinde bulunamadigi  icin 
* global degiskenin kapladigi alan olan 4 ekrana basilir. 
* struct  yapisinin bulunamamasinin sebebi C'de bunun  "struct nec" ismiyle kullanim 
* zorunlulugundan kaynaklanmaktadir. Buna typedef bildirimi  denilmektedir.
*/


//#### Bu kod C dilinin kurallarına göre derlenirse ne olur? C++ dilinin kurallarına göre derlenirse ne olur? Açıklayınız.


//[ödevin cevabı](https://vimeo.com/432180310)
