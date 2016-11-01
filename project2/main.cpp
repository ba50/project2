#include <iostream>
#include <vector>
#include <memory>

#include "dane_stat.hpp"
#include "rozklad.hpp"

int main() {
	try {
		// WskaŸniki do obiektów przechowuj¹cych dane
		std::vector <std::shared_ptr <DaneStat>> dane_vector;

	//	dane_vector.push_back(std::make_shared<DaneStatProxy>("program02_gauss_01m_1002_15.dat"));
		for (auto& dane : dane_vector) {
			dane->dane();
		}

		// Rejestrujemy wtyczki
		FabrykaRozkladow::rejestruj(&RozkladGaussa::kreator, std::string
		("Rozklad Gaussa"));
		FabrykaRozkladow::rejestruj(&RozkladGaussa::kreator, std::string
		("Rozklad Gaussa"));
/*		FabrykaRozkladow::rejestruj(&RozkladLorentza::kreator, std::string
		("Rozklad Lorentza"));
		FabrykaRozkladow::rejestruj(&RozkladPoisson::kreator, std::string
		("Rozklad Poissona"))*/;

		// Tworzy miziadelko do obliczania statystyk
		/*std::auto_ptr <Rozklad> rozkl(FabrykaRozkladow::utworz(wybor_r, dane[wybor - 1]->dane()));*/

		getchar();
	} catch (std::string s) {
		std::cout << s << std::endl;
		getchar();
	}

	return 0;
}