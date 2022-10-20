
// #### C dili tekrarı için sorulmaktadır: <br>
// Aşağıdaki kod hakkında yorum yapınız. 
// Bu kodda bir sentaks hatası var mı? 
// Yok ise, bu kod çalıştırılırsa standart çıkış akımına ne yazılır? 
// Bir derleyici ya da IDE kullanmadan yanıt veriniz.

#include <stdio.h>

int main()
{
	const int x = 55;
	int *ptr = (int *)&x;
	*ptr = 99;
	/*
	// C++ dilinde* "const int*" turunden "int* " turune implicit (ortulu donusum yoktur.)
	// Fakat burada  (int*) ile donusum islemi gerceklestirilmis ve legalite saglanmistir. 
	// Fakat *ptr = 99; ifadesinde bu legaliteye ragmen dilde herhangi  bir sentaks hatasi olmamasina ragmen 
	// const int bir nesnenin degeri degistirilmeye calisilmistir. Burada elde edilecek cikti  tanimsizdir. (Undefined behaviour)
	*/
	printf("x = %d\n", x);
}

// [Ödevin cevabı](https://vimeo.com/432190808)
