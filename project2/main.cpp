#include <vector>
#include <memory>

#include "dane_stat.hpp"
#include "rozklad.hpp"

int main() {

	// WskaŸniki do obiektów przechowuj¹cych dane
	std::vector <std::shared_ptr <DaneStat> > dane;

	// Rejestrujemy wtyczki
	/*FabrykaRozkladow::rejestruj(&RozkladGaussa::kreator, std::string
	("Rozklad Gaussa"));
	FabrykaRozkladow::rejestruj(&RozkladLorentza::kreator, std::string
	("Rozklad Lorentza"));
	FabrykaRozkladow::rejestruj(&RozkladPoisson::kreator, std::string
	("Rozklad Poissona"));*/

	// Tworzy miziadelko do obliczania statystyk
	/*std::auto_ptr <Rozklad> rozkl(FabrykaRozkladow::utworz(wybor_r, dane
		[wybor - 1]->dane()));*/

	return 0;
}