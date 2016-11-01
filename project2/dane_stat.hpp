#pragma once

#include <string>
#include <vector>
#include <memory>


class DaneStat // klasa bazowa
{

public:
	DaneStat(const std::string &nazwa);

	// zwraca referencje na przechowywane dane
	virtual const std::vector <float> &dane() const = 0;
	virtual ~DaneStat() {};
	virtual const std::string &nazwa() const; // zwraca nazwe pliku

protected:
	std::string nazwa_; // nazwa pliku
};


// proxy - wczytuje prawdziwy obiekt przy pierwszym u¿yciu
class DaneStatProxy : public DaneStat
{
	std::shared_ptr<DaneStat> dane_;
public:
	DaneStatProxy(const std::string nazwa) : DaneStat(nazwa), dane_(nullptr)
	{};
	~DaneStatProxy() {};
	virtual const std::vector <float> &dane() const {
		if (!dane_) dane_ = std::make_shared<DaneStat> DaneStatReal(nazwa_);
	}
};


// "prawdziwy" obiekt przechowujacy dane
class DaneStatReal : public DaneStat
{

public:
	DaneStatReal(const std::string nazwa) : DaneStat(nazwa) {};
};