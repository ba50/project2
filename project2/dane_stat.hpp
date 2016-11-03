#pragma once


#include <string>
#include <vector>
#include <memory>
#include <fstream>


class DaneStat // klasa bazowa
{

public:
	DaneStat(const std::string &nazwa) : nazwa_(nazwa){};

	// zwraca referencje na przechowywane dane
	virtual const std::vector <float> &dane() = 0;
	virtual ~DaneStat() {};
	virtual const std::string &nazwa() { // zwraca nazwe pliku
		return nazwa_;
	}

protected:
	std::string nazwa_; // nazwa pliku
};


// "prawdziwy" obiekt przechowujacy dane
class DaneStatReal : public DaneStat
{

	 std::vector <float> dane_;

public:
	DaneStatReal(const std::string nazwa) : DaneStat(nazwa) {
		std::ifstream in_file(nazwa);
		dane_.reserve(1000000);
		 float temp;
		if (in_file.is_open()) {
			while (in_file >> temp) {
				dane_.push_back(temp);
			}
		}
		else {
			throw std::string("Nie udalo sie otworzyc pliku: " + nazwa);
		}

	};
	const std::vector <float> &dane() override {
		return dane_;
	}

};


// proxy - wczytuje prawdziwy obiekt przy pierwszym użyciu
class DaneStatProxy : public DaneStat
{
	std::shared_ptr<DaneStat> dane_stat;
public:
	DaneStatProxy(const std::string nazwa) : DaneStat(nazwa), dane_stat(nullptr) {};
	const std::vector <float> &dane() override {
		if (!dane_stat) dane_stat = std::make_shared<DaneStatReal>(DaneStatReal(nazwa_));

		if (!dane_stat) throw std::string("puste dane_stat!\n");
		return dane_stat->dane();
	}
};
