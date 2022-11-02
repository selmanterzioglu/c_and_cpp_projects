// #### C++17 standartlarına göre aşağıdaki C++ programı çalıştırıldığında bu programın çıktısı ne olur?

#include <iostream>
 
int main()
{
	int ival = 0;	//Doktor bu ne ??/
	// 0 int ival  degiskeni 0 olarak initialize edilmektedir. 
	// int ival{};  yazim bicimi  de ival  degerini 0 olarak  baslatacaktir. 

	ival = 1;
	std::cout << ival;	
}

// __Sorunun yanıtı şu seçeneklerden biri de olabilir:__

// + Sentaks hatası *(syntax error)*
// + Tanımsız davranış *(undefined behavior)*
// + Derleyiciye göre değişir *(implementation defined)*
