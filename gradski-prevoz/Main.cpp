#include "Network.h"

void selectZone(Network *n);
void filterByNumber(Network *n);
void filterByNumberOfStations(Network *n);
void mainMenu();
void groupMode(Network *n);
void groupModeMenu(Network *n);
void groupModeMenuText();
void closestStation(Network* n);
void stations1DistanceAway(Network *n);

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
	while (1) {
		groupModeMenu(n);
	}
	(*n).~Network();
	
}

void groupModeMenu(Network *n)
{
	int control;
	int number;
	int number2;
	double latitude;
	double longitude;
	string line;
	Station *s;
	do {
		groupModeMenuText();
		cin >> control;
	} while (control < 0 && control>10);

	switch (control)
	{
	case 1:
		cout << *n;
		break;
	case 2://Odredjivanje skupa linija sa kojima data linija ima zajednicka stajalista(bez obzira na smer kretanja)
		cout << "Unesite sifru linije, velikim slovima slova\n";
		cin >> line;
		n->getLinesWithMutualStations(line);
		cout << "\n";
		break;
	case 3://Odredjivanje da li data linija prolazi kroz zadata dva stajalista u istom smeru svog kretanja
		cout << "Unesite sifru linije, velikim slovima\n";
		cin >> line;
		cout << "Unesite sifru prvog stajalista\n";
		cin >> number;
		cout << "Unesite sifru drugog stajalista\n";
		cin >> number2;
		if (n->areStationsOnSameLineAndDirection(line, number, number2))
			cout << "Jesu\n";
		else
			cout << "Nisu\n";
		break;
	case 4://Odredjivanje linije sa kojom data linija ima najvise zajednickih stajalista
		cout << "Unesite sifru linije, velikim slovima\n";
		cin >> line;
		cout << n->lineWithMostMutualStation(line)->getCode() << "\n";
		break;//TODO: Prikaz svih maksimalnih
	case 5://Odredjivanje najblizeg stajalista u odnosu na zadatu geografsku lokaciju, 
		   //uz mogucnost odredjivanja najblizeg stajalista samo odredjenje linije
		closestStation(n);
		break;
	case 6://Odredjivanje broja zajednickih stajalista za sve parove linija koje imaju zajednicko stajaliste,
		   //uz mogucnost filtriranja na parove linija koje imaju zajednickih stajalista vise od zadatog broja
		break;
	case 7://Odredjivanje svih linija koje prolaze kroz dato stajaliste
		cout << "Unesite sifru stajalista\n";
		cin >> number;
		s = Station::getStation(number);
		for (auto it = s->getLinesBegin(); it != s->getLinesEnd(); ++it)
			cout << it->first << " ";
		cout << "\n";
		break;
	case 8:
		stations1DistanceAway(n);
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

void closestStation(Network* n) {
	double latitude;
	double longitude;
	int number;
	string line;
	cout << "Unesite geografsku sirinu lokacije\n";
	cin >> latitude;
	cout << "Unesite geografsku duzinu lokacije\n";
	cin >> longitude;
	cout << "Za specificiranje linije unesite 1, u suprotnom 0\n";
	cin >> number;
	if (number == 1)
	{
		cout << "Unesite sifru linije, velikim slovima\n";
		cin >> line;
	}
	else
		line = "";
	cout << "Najblize stajaliste je: " << *(n->closestStation(latitude, longitude, line)) << "\n";
}

void stations1DistanceAway(Network *n)
{
	int number;
	cout << "Unesite sifru stajalista\n";
	cin >> number;
	Station *s = Station::getStation(number);
	for (auto it = s->getLinesBegin(); it != s->getLinesEnd(); ++it)
	{
		if (it->second->isStationOnLine(number, Direction::A))
		{
			for (auto it1 = it->second->getA_firstBegin(); it1 != it->second->getA_firstEnd(); ++it1)
			{
				if ((*it1)->getCode() == number)
				{
					++it1;
					cout << *(*it1) << "\n";
					break;
				}
			}
		}
		else
		{
			for (auto it1 = it->second->getB_lastBegin(); it1 != it->second->getB_lastEnd(); ++it1)
			{
				if ((*it1)->getCode() == number)
				{
					++it1;
					cout << *(*it1) << "\n";
					break;
				}
			}
		}
	}
}