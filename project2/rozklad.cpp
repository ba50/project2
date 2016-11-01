//#include "rozklad.hpp"
//
//
//std::auto_ptr<ParametryRozkladu> RozkladGaussa::oblicz() const
//{
//	return std::auto_ptr<ParametryRozkladu>();
//}
//
//
//// Statyczny kreator wybranej klasy (to naprawdê jest takie proste!)
//Rozklad *RozkladGaussa::kreator(const std::vector <float> &dane)
//{
//	return new RozkladGaussa(dane);
//}
//
//
//void FabrykaRozkladow::rejestruj(KreatorRozkladu kr, const std::string & nazwa)
//{
//}
//
//
////// Statyczna metoda wo³aj¹ca (choæ trudno to zobaczyæ) kreator typu o podanym id
////Rozklad *FabrykaRozkladow::utworz(unsigned typ, const std::vector <float> &dane)
////{
////	return rozklady[typ](dane);
////}
//
//
//std::string FabrykaRozkladow::nazwa(unsigned id)
//{
//	return std::string();
//}
//
//
//Rozklad::Rozklad(const std::vector<float>& dane) : dane_(dane)
//{
//}
