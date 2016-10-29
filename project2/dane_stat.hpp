#ifndef _dane_stat_hpp_
#define _dane_stat_hpp_
#include <string>
#include <vector>
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
};
// "prawdziwy" obiekt przechowujacy dane
class DaneStatReal : public DaneStat
{
};
#endif
