//#### Aşağıdaki C++ programı hakkında yorum yapınız:

//+ sentaks hatası
//+ tanımsız davranış
//+ derleyiciye göre değişir
//+ ekrana şunu yazar: 

#include <iostream> 

typedef long long mylong;

void func(unsigned mylong)
{
	std::cout << '1';
}

void func(unsigned long long) 
{
	std::cout << '2';
}

int main() 
{
	func(0ULL);
}
//yukarida function overloading resolution yoktur. 
// ilk fonksiyondaki unsigned int turunden bir parametredir .
// 2. fonksiyon unsigned int long long turunden bir parametre almaktadir .
// Bu sebeple main  icerisindeki  cagri 2. func fonksiyonunu cagiracak ve ekrana 2 basilacaktir.

//[ödevin cevabı](https://vimeo.com/443981524]
