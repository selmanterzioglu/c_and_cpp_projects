/*
#### C dili tekrarı için sorulmaktadır:</br>
Aşağıdaki kodda C ve C++ dillerinin kurallarına göre sentaks hatası oluşturan deyimleri *(statements)* işaretleyiniz 
ve sentaks hatalarının nedenlerini açıklayınız.
Her bir gösterici *(pointer)* değişkeni niteleyen ingilizce terimleri yazınız. 
Soruya bir derleyici, *IDE* ya da yardımcı bira araç kullanmadan yanıt veriniz.
*/

int main()
{
	int x = 10;
	int y = 20;
	
	int * const p1 = &x;
	const int *p2 = &x;
	int const *p3 = &x;
	const int* const p4 = &x;

	*p1 = 40;
	p1 = &y;
	/*
	// buradaki hatanin sebebi const pointer to int olarak tanimlanmis 
	// (yani sadece o  bellek alanini gostermeyi taahhut eden )bir pointer'in
	// daha sonra baska bir bellek alanini gostermek uzere kullanilmis olmasidir.
	*/

	*p2 = 40;
	/*
	// yukaridaki  hatanin sebebi pointer to const int olarak tanimlanmis olan
	// (adresini gosterdigi degiskenin degerini degistirmemeyi taahhut etmis) pointer'in
	// onun degerini degistirmeye calismasindan kaynaklanmaktadir. 
	*/
	p2 = &y;

	*p3 = 40;
	/*
	Bir ustte aciklanan hatadan bir farki yoktur. 
	"const int *p" ile "int const *p" arasinda bir fark yoktur.  
	*/
	p3 = &y;
	
	*p4 = 40;
	/*
	// Yukaridaki  hatanin sebebi const pointer to const int olan (hem farkli  bir bellek adresini gostermeyecegini 
	// hem de adresini gosterdigi  degiskenin icerigini  degistirmeyecegini taahhut etmis)
	// pointer'in adresini  gosterdigi  degiskenin degerini  degistirmek istemesidir. 
	*/
	p4 = &y;
	/*
	// const pointer to const int olan bir pointer'in baska bir bellek alanini isaret etmeye calismasidir.
	*/
}


// [ödev cevabı](https://vimeo.com/432186814)
