#pragma once

#include <map>
#include <vector>
#include <math.h>
#include <algorithm>


enum class Parametr {
	mean,
	variance,
	standard_deviation,
};


// Mapa przechowujaca obliczone estymatory rozkladu: opis-wartosc
typedef std::map <Parametr, float> ParametryRozkladu;


class Rozklad // ATD - klasa bazowa dla "obliczaczy" estymatorow
{

public:
	// ustawia referencje na dane do analizy
	explicit Rozklad(const std::vector <float> &dane) :
		dane_(dane) {};
	virtual ~Rozklad() {};
	// oblicza estymatory i zwraca je w mapie
	virtual std::unique_ptr <ParametryRozkladu> oblicz() const = 0;

protected:
	// przechowuje referencje na dane do analizy
	const std::vector <float> &dane_;

	void  parametry_std(ParametryRozkladu &parametry) const {

		parametry[Parametr::mean] = 0.f;
		for (auto obj : dane_) {
			parametry[Parametr::mean] += obj;
		}
		parametry[Parametr::mean] /= dane_.size();

		parametry[Parametr::variance] = 0.f;
		auto odh = [&parametry](float x) {
			parametry[Parametr::variance] += pow(x - parametry[Parametr::mean], 2);
		};
		std::for_each(dane_.begin(), dane_.end(), odh);
		parametry[Parametr::variance] /= dane_.size();
		parametry[Parametr::standard_deviation] = sqrtf(parametry[Parametr::variance]);

	}
};


class RozkladGaussa : public Rozklad
{

public:
	// nie robi nic sensownego poza wywolaniem konstr. klasy bazowej z odpowiednim parametrem
	explicit RozkladGaussa(const std::vector <float> &dane) : Rozklad(dane) {};
	~RozkladGaussa() {};
	// liczy wartosc srednia i odchylenie standardowe
	std::unique_ptr <ParametryRozkladu> oblicz() const override {
		ParametryRozkladu parametry;

		parametry_std(parametry);

		return std::make_unique<ParametryRozkladu>(parametry);
	}

	// statyczna met. tworzaca i zwracajaca wskaznik na obiekt wlasnego typu
	static Rozklad *kreator(const std::vector <float> &dane) {
		return new RozkladGaussa(dane);
	};
};


class RozkladLorentza : public Rozklad
{

public:
	// nie robi nic sensownego poza wywolaniem konstr. klasy bazowej z odpowiednim parametrem
	explicit RozkladLorentza(const std::vector <float> &dane) : Rozklad(dane) {};
	~RozkladLorentza() {};
	// liczy wartosc srednia i odchylenie standardowe
	std::unique_ptr <ParametryRozkladu> oblicz() const override {
		ParametryRozkladu parametry;

		parametry_std(parametry);

		return std::make_unique<ParametryRozkladu>(parametry);
	}

	// statyczna met. tworzaca i zwracajaca wskaznik na obiekt wlasnego typu
	static Rozklad *kreator(const std::vector <float> &dane) {
		return new RozkladLorentza(dane);
	};
};


// wskaznik typu KreatorRozkladu do funkcji tworzacej obiekt
// obliczacza rozkladu (pochodna klasy Rozklad)
typedef Rozklad* (*KreatorRozkladu)(const std::vector <float> &);


class FabrykaRozkladow // FABRYKA! :)
{

	// przechowuje wskaźniki kreatorow (funkcji tworzących!)
	static std::map <unsigned, KreatorRozkladu> rozklady;

	// przechowuje nazwy rozkladow
	static std::map <unsigned, std::string> nazwy;

	//rejestruje kolejne rozklady
	static unsigned id;

public:
	// rejestruje kreator danego rozkladu (id generowane przyrostowo od 1)
	static void rejestruj(KreatorRozkladu kr, const std::string &nazwa) {
	
		nazwy[id] = nazwa;
		rozklady[id] = kr;
		id++;
	};
	// wola kreator dla rozkladu o wybranym id
	static Rozklad *utworz(unsigned id, const std::vector <float> &dane) {
		return rozklady[id](dane);
	};
	// zwraca nazwe rozkladu o identyfikatorze id
	static std::string nazwa(unsigned id) {
		return nazwy[id];
	}
	// zwraca liczbe zarejestrowanych rozkladow
	static unsigned ilosc() {
		return static_cast<unsigned>(rozklady.size());
	}
};

unsigned FabrykaRozkladow::id = 0;
std::map <unsigned, KreatorRozkladu> FabrykaRozkladow::rozklady;
std::map <unsigned, std::string> FabrykaRozkladow::nazwy;
