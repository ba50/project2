#include <iostream>
#include <vector>
#include <memory>

#include "dane_stat.hpp"
#include "rozklad.hpp"

int main() {
	try {
		// WskaŸniki do obiektów przechowuj¹cych dane
		std::vector <std::shared_ptr <DaneStat>> dane_vector;

		dane_vector.push_back(std::make_shared<DaneStatProxy>("dev.dat"));
		for (auto& dane : dane_vector) {
			dane->dane();
		}

		// Rejestrujemy wtyczki
		FabrykaRozkladow::rejestruj(&RozkladGaussa::kreator, std::string
		("Rozklad Gaussa"));
/*		FabrykaRozkladow::rejestruj(&RozkladLorentza::kreator, std::string
		("Rozklad Lorentza"));
		FabrykaRozkladow::rejestruj(&RozkladPoisson::kreator, std::string
		("Rozklad Poissona"))*/;

		unsigned wybor_r(0), wybor(1);

		// Tworzy miziadelko do obliczania statystyk
		std::unique_ptr <Rozklad> rozkl(
			FabrykaRozkladow::utworz(wybor_r, dane_vector[wybor - 1]->dane()));

		std::unique_ptr <ParametryRozkladu> temp = rozkl->oblicz();
		for (auto& obj : *temp) {
			std::cout << obj.first << ": " << obj.second << std::endl;
		}

		getchar();

		return 0;
	} catch (std::string s) {
		std::cout << s << std::endl;
		getchar();

		return 1;
	}

}