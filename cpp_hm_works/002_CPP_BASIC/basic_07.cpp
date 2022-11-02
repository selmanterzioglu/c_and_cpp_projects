// #### C++17 standartlarına göre aşağıdaki C++ programı çalıştırıldığında bu programın çıktısı ne olur?

/*
// int degeri maksimum tutabilecegi  rakami  tuttugu icin bir arttirildiginda 
// minimum degerine cekilir. bu da - bir deger olmus olur.  
*/

#include <iostream>
#include <limits>
 
int main() 
{
	auto x = std::numeric_limits<int>::min();
	std::cout << ++x;
}

// __Sorunun yanıtı şu seçeneklerden biri de olabilir:__

// + Sentaks hatası *(syntax error)*
// + Tanımsız davranış *(undefined behavior)*
// + Derleyiciye göre değişir *(implementation defined)*
