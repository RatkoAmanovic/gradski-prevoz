#include "Network.h"

void selectZone(Network *n);
void filterByNumber(Network *n);
void filterByNumberOfStations(Network *n);
void mainMenu();
void groupMode(Network *n);
void groupModeMenu(Network *n); 
void groupModeMenuText();

int main()
{
	Network network;
	int control;
	string line;
	while (1) {
		do
		{
			mainMenu();
			cin >> control;
		} while (control<0 || control>2);
		
		switch (control)
		{
		case 1:
			groupMode(&network);
			break;
		case 2:
			cout << "Unesite koju liniju zelite da pregledate\n";
			cin >> line;
			network.readLine(line);
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	}
}

void selectZone(Network *n)
{
	int zone;
	do {
		cout << "Unesite koje zone zelite?\n";
		cout << "1. 1.\n";
		cout << "2. 1. i 2.\n";
		cout << "3. 1. 2. i 3.\n";
		cout << "4. Sve zone\n";
		cout << "0. Izlaz\n";
		cin >> zone;
	} while (zone < 0 || zone>4);

	switch (zone)
	{
	case 1:
		n->setZone(1);
		break;
	case 2:
		n->setZone(2);
		break;
	case 3:
		n->setZone(3);
		break;
	case 4:
		n->setZone(4);
		break;
	case 0:
		exit(0);
		break;
	default:
		break;
	}
}

void filterByNumber(Network *n)
{
	int control;
	int number;
	do {
		cout << "Filtriranje prema broju?\n";
		cout << "1. Manje od zadatog broja\n";
		cout << "2. Vece od zadatog broja\n";
		cout << "3. U opsegu od prvog broja do drugog broja\n";
		cout << "4. Bez filtera\n";
		cout << "0. Izlaz\n";
		cin >> control;
	} while (control < 0 || control>4);

	switch (control)
	{
	case 1:
		cout << "Unesite broj od koga zelite da brojevi linija budu manji\n";
		cin >> number;
		n->setNumberMax(number);
		break;
	case 2:
		cout << "Unesite broj od koga zelite da brojevi linija budu veci\n";
		cin >> number;
		n->setNumberMin(number);
		break;
	case 3:
		cout << "Unesite broj od koga zelite da brojevi linija budu veci\n";
		cin >> number;
		n->setNumberMin(number);
		cout << "Unesite broj od koga zelite da brojevi linija budu manji\n";
		cin >> number;
		n->setNumberMax(number);
		break;
	case 4:
		break;
	case 0:
		exit(0);
		break;
	default:
		break;
	}
}

void filterByNumberOfStations(Network *n)
{
	int control;
	int number;
	do {
		cout << "Filtriranje prema broju stainca?\n";
		cout << "1. Manje od zadatog broja\n";
		cout << "2. Vece od zadatog broja\n";
		cout << "3. Bez filtera\n";
		cout << "0. Izlaz\n";
		cin >> control;
	} while (control < 0 || control>3);

	switch (control)
	{
	case 1:
		cout << "Unesite broj od koga zelite da brojevi linija budu manji\n";
		cin >> number;
		n->setMaxNumberOfStations(number);
		break;
	case 2:
		cout << "Unesite broj od koga zelite da brojevi linija budu veci\n";
		cin >> number;
		n->setMinNumberOfStations(number);
		break;
	case 3:
		break;
	case 0:
		exit(0);
		break;
	default:
		break;
	}
}

void mainMenu() {
	cout << "Unesite koji rezim rada zelite?\n";
	cout << "1. Grupni rezim rada\n";
	cout << "2. Pojedinacni rezim rada\n";
	cout << "0. Izlaz\n";
}

void groupMode(Network *n)
{
	selectZone(n);
	filterByNumber(n);
	filterByNumberOfStations(n);
	(*n).readLines();
	groupModeMenu(n);
	(*n).~Network();
}

void groupModeMenu(Network *n)
{
	int control;
	int number;
	do {
		groupModeMenuText();
		cin >> control;
	} while (control < 0 && control>10);

	switch (control)
	{
	case 1:
		cout << *n;
		break;
	case 2:
		cout << "Unesite broj od koga zelite da brojevi linija budu veci\n";
		cin >> number;
		n->setNumberMin(number);
		break;
	case 3:
		cout << "Unesite broj od koga zelite da brojevi linija budu veci\n";
		cin >> number;
		n->setNumberMin(number);
		cout << "Unesite broj od koga zelite da brojevi linija budu manji\n";
		cin >> number;
		n->setNumberMax(number);
		break;
	case 4:
		break;
	case 0:
		exit(0);
		break;
	default:
		break;
	}
}

void groupModeMenuText()
{
	cout << "Izaberite aktivnost koju zelite da izvrsite!\n";
	cout << "1.  Stampanje mreze\n";
	cout << "2.  Odredjivanje skupa linija sa kojima data linija ima zajednicka stajalista(bez obzira na smer kretanja)\n";
	cout << "3.  Odredjivanje da li data linija prolazi kroz zadata dva stajalista u istom smeru svog kretanja\n";
	cout << "4.  Odredjivanje linije sa kojom data linija ima najvise zajednickih stajalista\n";
	cout << "5.  Odredjivanje najblizeg stajalista u odnosu na zadatu geografsku lokaciju,\n    uz mogucnost odredjivanja najblizeg stajalista samo odredjenje linije\n";
	cout << "6.  Odredjivanje broja zajednickih stajalista za sve parove linija koje imaju zajednicko stajaliste, \n    uz mogucnost filtriranja na parove linija koje imaju zajednickih stajalista vise od zadatog broja\n";
	cout << "7.  Odredjivanje svih linija koje prolaze kroz dato stajaliste\n";
	cout << "8.  Odredjivanje svih stajalista do kojih je moguce stici iz zadatog stajalista uz voznju maksimalno jednu stanicu\n";
	cout << "9.  Odredjivanje najmanjeg potrebnog broja presedanja na putu izmedju dva zadata stajalista\n";
	cout << "10. Odredjivanje najkraceg puta izmedju dva stajalista(ne uzimati u obzir geografsku lokaciju,\n    vec za najkraci put uzeti onaj koji se sastoji od najmanjeg broja stajalista)\n";
	cout << "0.  Izlaz\n";
}