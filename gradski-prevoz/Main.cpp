#include "Network.h"

void selectZone(Network *n);
void filterByNumber(Network *n);
void filterByNumberOfStations(Network *n);

int main()
{
	Network network;
	int control;
	string line;
	while (1) {
		do
		{
			cout << "Unesite koji rezim rada zelite?\n";
			cout << "1. Grupni rezim rada\n";
			cout << "2. Pojedinacni rezim rada\n";
			cout << "0. Izlaz\n";
			cin >> control;
		} while (control<0 && control>2);
		switch (control)
		{
		case 1:
			selectZone(&network);
			filterByNumber(&network);
			filterByNumberOfStations(&network);
			network.readLines();
			cout << network;
			network.~Network();
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
	} while (zone < 0 && zone>4);

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
	} while (control < 0 && control>4);

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
	} while (control < 0 && control>4);

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