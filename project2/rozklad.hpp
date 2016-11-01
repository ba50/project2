#pragma once

#include <map>
#include <vector>


// Mapa przechowujaca obliczone estymatory rozkladu: opis-wartosc
typedef std::map <std::string, float> ParametryRozkladu;


class Rozklad // ATD - klasa bazowa dla "obliczaczy" estymatorow
{

public:
	// ustawia referencje na dane do analizy
	explicit Rozklad(const std::vector <float> &dane) :
		dane_(dane) {};
	virtual ~Rozklad() {};
	// oblicza estymatory i zwraca je w mapie
	virtual std::auto_ptr <ParametryRozkladu> oblicz() const = 0;

protected:
	// przechowuje referencje na dane do analizy
	const std::vector <float> &dane_;

};


class RozkladGaussa : public Rozklad
{

public:
	// nie robi nic sensownego poza wywolaniem konstr. klasy bazowej z odpowiednim parametrem
	explicit RozkladGaussa(const std::vector <float> &dane) : Rozklad(dane) {};
	~RozkladGaussa() {};
	// liczy wartosc srednia i odchylenie standardowe
	std::auto_ptr <ParametryRozkladu> oblicz() const override {
		return std::auto_ptr<ParametryRozkladu>();
	}

	// statyczna met. tworzaca i zwracajaca wskaznik na obiekt wlasnego typu
	static Rozklad *kreator(const std::vector <float> &dane) {
		return new RozkladGaussa(dane);
	};
};



// wskaznik typu KreatorRozkladu do funkcji tworzacej obiekt
// obliczacza rozkladu (pochodna klasy Rozklad)
typedef Rozklad* (*KreatorRozkladu)(const std::vector <float> &);


class FabrykaRozkladow // FABRYKA! :)
{

	// przechowuje wskaüniki kreatorow (funkcji tworzπcych!)
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