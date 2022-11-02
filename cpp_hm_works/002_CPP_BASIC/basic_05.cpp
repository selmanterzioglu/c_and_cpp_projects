// <!-- #### C++17 standartlarına göre aşağıdaki C++ programı çalıştırıldığında bu programın çıktısı ne olur? -->

#include <iostream>
 
size_t getSize_1(int* a)
{
	std::cout << "getsize_1 &a= " << &a  << "\n";
	return sizeof a;
}
 
size_t getSize_2(int a[])
{
	std::cout << "getsize_2 &a= " << &a  << "\n";
	return sizeof *a;
}
 
size_t getSize_3(int(&a)[10])
{
	std::cout << "getsize_3 &a= " << &a  << "\n";
	return sizeof a;
}
 
int main()
{
	int a[10] = { 0 };
	
	std::cout << (sizeof(a) == getSize_1(a));
	std::cout << (sizeof(a) == getSize_2(a));
	std::cout << (sizeof(a) == getSize_3(a));
}

// __Sorunun yanıtı şu seçeneklerden biri de olabilir:__

// + Sentaks hatası *(syntax error)*
// + Tanımsız davranış *(undefined behavior)*
// + Derleyiciye göre değişir *(implementation defined)*
