#include <iostream>
#include <vector>
#include <memory>

#include "dane_stat.hpp"
#include "rozklad.hpp"


// Enum to string
auto etos(Parametr parametr) {
	const std::map<Parametr, std::string> parametry_nazwa{
		{Parametr::mean, "mean"},
		{Parametr::variance, "variance"},
		{Parametr::standard_deviation, "standard_deviation"},
	};

	auto it = parametry_nazwa.find(parametr);
	return it == parametry_nazwa.end() ? "Out of range" : it->second;
};


int main() {
	try {
		bool quit = false;
		std::vector <std::shared_ptr <DaneStat>> dane_vector;
		while (!quit) {
			// Wskaźniki do obiektów przechowujących dane

			std::vector<std::string> nazwy_plikow;
			nazwy_plikow.push_back("dev.dat");
			nazwy_plikow.push_back("program02_gauss_01m_1002_15.dat");
			nazwy_plikow.push_back("program02_gauss_02m_102_3.dat");
			nazwy_plikow.push_back("program02_gauss_05m_3333_113.dat");
			nazwy_plikow.push_back("program02_lorentz_01m_1004_2.dat");
			nazwy_plikow.push_back("program02_lorentz_02m_0098_5.dat");
			nazwy_plikow.push_back("program02_lorentz_05m_4000_200.dat");
			nazwy_plikow.push_back("program02_lorentz_10m_2000_120.dat");
			nazwy_plikow.push_back("program02_poisson_02m_9000.dat");
			nazwy_plikow.push_back("program02_poisson_10m_7777.dat");
			nazwy_plikow.push_back("exit");

			printf("plik:\n");
			int i(0);
			for (auto obj : nazwy_plikow) {
				std::cout << "[" << i << "]" << obj << std::endl;
				dane_vector.push_back(std::make_shared<DaneStatProxy>(obj));
				i++;
			}

			unsigned wybor_r(0), wybor(0);

			std::cin >> wybor;
			if (wybor >= nazwy_plikow.size()) throw std::string("Exit");
			dane_vector[wybor]->dane();
			printf("rozklad: \n");
			std::cin >> wybor_r;

			// Rejestrujemy wtyczki
			FabrykaRozkladow::rejestruj(&RozkladGaussa::kreator, std::string
			("Rozklad Gaussa"));
			FabrykaRozkladow::rejestruj(&RozkladLorentza::kreator, std::string
			("Rozklad Lorentza"));
			/*	FabrykaRozkladow::rejestruj(&RozkladPoisson::kreator, std::string
				("Rozklad Poissona"));*/


				// Tworzy miziadelko do obliczania statystyk
			std::unique_ptr <Rozklad> rozkl(FabrykaRozkladow::utworz(wybor_r, dane_vector[wybor]->dane()));

			std::unique_ptr<ParametryRozkladu> param = rozkl->oblicz();

			for (auto& obj : *param) {
				std::cout << etos(obj.first) << ": " << obj.second << std::endl;
			}
			rozkl.reset();
			printf("##########################################\n");
		}

		return 0;
	} catch (std::string s) {
		std::cout << s << std::endl;
		getchar();

		return 1;
	}

}
