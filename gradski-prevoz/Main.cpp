#include "Line.h"

int main()
{
	Station vuk(64, "Vukov spomenik", 44.8056059, 20.4783626, 1);
	Station vuk1(634, "Vukofqceqv spomenik", 64.8056059, 60.4783626, 6);

	cout << vuk << "\n";
	cout << vuk1 << "\n";

	Line semdescetiri("74", "Vukov spomenik", "Vukofqceqv spomeini");
	semdescetiri.addStationToA(vuk);
	semdescetiri.addStationToA(vuk1);

	cout << semdescetiri;
	semdescetiri.readStationsToA();
}