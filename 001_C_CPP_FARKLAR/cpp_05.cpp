// Aşağıdaki kaynak kod
// + C dilinin kurallarına göre derlenip çalıştırıldığında ne olur?
// + C++ dilinin kurallarına göre derlenip çalıştırıldığında ne olur?
// + **#include <stdbool.h>** Önişlemci komutu koda eklenerek 
// C dilinin kurallarına göre derlenip çalıştırıldığında ne olur?

#include <stdio.h>

int main()
{
	/**
	// C++ Dilinde true ifadesi  tanimli  bir sabit ifadesidir. Cikti "dogru" seklinde olacaktir.
	// C dilinde ise boyle tanimli  bir ifade yoktur.  Bu yuzden derleyici  bu tanimi "0" kabul ederek
	// Cikti "yanlis" seklinde olacaktir. 
	// Fakat sdtbool.h kutuphanesinde true ve false tam sayi tanimli  bir makrodur. 
	// C dilinde bu kutuphane eklenerek calistirildiginda Cikti "dogru" seklinde olacaktir.
	*/
#if true
	printf("dogru\n");
#else
	printf("yanlis\n");
#endif

}

// [ödev cevabı](https://vimeo.com/362520568)
