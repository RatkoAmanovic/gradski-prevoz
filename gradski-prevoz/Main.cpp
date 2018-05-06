#include "Network.h"
#include "Generator.h"
#include "ClearScreen.h"

void selectZone(Network *n);
void filterByNumber(Network *n);
void filterByNumberOfStations(Network *n);
void mainMenu();
void groupMode(Network *n);
void groupModeMenu(Network *n);
void groupModeMenuText();
void closestStation(Network* n);
void stations1DistanceAway(Network *n);
void graphGenerating(Network *n);
void graphGeneratingText();
void lineManipulation(Network* n);
void lineManipulationText();
void exitProgram(Network *n);
void pauseScreen();

bool graphGenerated = false;

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
			cout << network;
			pauseScreen();
			network.~Network();
			break;
		case 0:
			exitProgram(&network);
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
		exitProgram(n);
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
		exitProgram(n);
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
		exitProgram(n);
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
	clearScreen();
	selectZone(n);

	clearScreen();
	filterByNumber(n);

	clearScreen();
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
	string line;
	Station *s;
	unordered_map<pair<string, string>, int, Network::pair_hash> map;
	unordered_set<Line *> mutualLines;
	do {
		groupModeMenuText();
		cin >> control;
	} while (control < 0 && control>11);

	switch (control)
	{
	case 1:
		cout << *n;
		cout << "Unestite bilo koji broj da bi ste nastavili sa radom\n";
		cin >> number;
		break;
	case 2://Odredjivanje skupa linija sa kojima data linija ima zajednicka stajalista(bez obzira na smer kretanja)
		cout << "Unesite sifru linije, velikim slovima slova\n";
		cin >> line;
		mutualLines =  n->getLinesWithMutualStations(line);
		for (auto it = mutualLines.begin(); it != mutualLines.end(); ++it)
		{
			cout << (*it)->getCode() << " ";
		}
		cout << "\n";
		pauseScreen();
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
		pauseScreen();
		break;
	case 4://Odredjivanje linije sa kojom data linija ima najvise zajednickih stajalista
		cout << "Unesite sifru linije, velikim slovima\n";
		cin >> line;
		cout << n->lineWithMostMutualStation(line)->getCode() << "\n";
		pauseScreen();
		break;//TODO: Prikaz svih maksimalnih
	case 5://Odredjivanje najblizeg stajalista u odnosu na zadatu geografsku lokaciju, 
		   //uz mogucnost odredjivanja najblizeg stajalista samo odredjenje linije
		closestStation(n);
		pauseScreen();
		break;
	case 6://Odredjivanje broja zajednickih stajalista za sve parove linija koje imaju zajednicko stajaliste,
		   //uz mogucnost filtriranja na parove linija koje imaju zajednickih stajalista vise od zadatog broja
		n->numberOfMutualStationsForAllLines();
		pauseScreen();
		break;
	case 7://Odredjivanje svih linija koje prolaze kroz dato stajaliste
		cout << "Unesite sifru stajalista\n";
		cin >> number;
		s = Station::getStation(number);
		if (s != nullptr)
		{
			for (auto it = s->getLinesBegin(); it != s->getLinesEnd(); ++it)
				cout << it->first << " ";
			cout << "\n";
		}
		else
		{
			cout << "To stajaliste ne postoji\n";
		}
		pauseScreen();
		break;
	case 8://Odredjivanje svih stajalista do kojih je moguce stici iz zadatog stajalista uz voznju maksimalno jednu stanicu
		stations1DistanceAway(n);
		pauseScreen();
		break;
	case 9://Odredjivanje najmanjeg potrebnog broja presedanja na putu izmedju dva zadata stajalista
		cout << "Unesite sifru prvog stajalista\n";
		cin >> number;
		cout << "Unesite sifru drugog stajalista\n";
		cin >> number2;
		cout << "Najmanji broj presedanja je: " << n->leastTransfersBetweenStations(number, number2) << "\n";
		pauseScreen();
		break;
	case 10://Odredjivanje najkraceg puta izmedju dva stajalista(ne uzimati u obzir geografsku lokaciju,\n    vec za najkraci put uzeti onaj koji se sastoji od najmanjeg broja stajalista)
		cout << "Unesite sifru prvog stajalista\n";
		cin >> number;
		cout << "Unesite sifru drugog stajalista\n";
		cin >> number2;
		cout << "Najmanji broj stajalista je: " << n->leastNumberOfStationsBetweenStations(number, number2) << "\n";
		pauseScreen();
		break;
	case 11:
		graphGenerating(n);
		break;
	case 12:
		lineManipulation(n);
		break;
	case 0:
		exitProgram(n);
		break;
	default:
		break;
	}
}

void groupModeMenuText()
{
	clearScreen();
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
	cout << "11. Generisanje grafovskih fajlova\n";
	cout << "12. Manipulacija nad linijama\n";
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
	unordered_map<int,Station*> s = n->stations1DistnaceAway(number);
	for (auto st : s)
		cout << *(st.second) << "\n";
}

void graphGenerating(Network *n)
{	
	int control;
	int number;
	do {
		graphGeneratingText();
		cin >> control;
	} while (control < 0 && control>2);

	switch (control)
	{
	case 1://L-model
		cout << "Za generisanje GML grafa pritisnite 1, a za CSV pritisnite 2\n";
		cin >> number;
		if (number == 1)
			Generator::generateGML_LTypeGraph(n);
		if (number == 2)
			Generator::generateCSV_LTypeGraph(n);
		graphGenerated = true;
		break;
	case 2://C-model
		cout << "Za generisanje GML grafa pritisnite 1, a za CSV pritisnite 2\n";
		cin >> number;
		if (number == 1)
			Generator::generateGML_CTypeGraph(n);
		if (number == 2)
			Generator::generateCSV_CTypeGraph(n);
		graphGenerated = true;
		break;
	case 0:
		exitProgram(n);
	default:
		break;
	}
}

void graphGeneratingText()
{
	clearScreen();
	cout << "Izaberite koji tip grafa zelite da izgenerisete\n";
	cout << "1. L-model(Stajalista cvorovi, linije grane)\n";
	cout << "2. C-model(Linije cvorovi, zajednicka stajalista grane)\n";
	cout << "0. Izlaz\n";
}

void lineManipulation(Network *n) {
	string line;
	string code;
	int control;
	int number;
	int number2;
	int number3;
	Station * s;
	cout << "Unesite sifru linije koju zelite da menjate\n";
	cin >> line;
	Line *l = n->getLine(line);
	if (l == nullptr)
	{
		cout << "Linija ne postoji";
		pauseScreen();
		return;
	}
	do {
		lineManipulationText();
		cin >> control;
	} while (control < 0 && control>5);

	switch (control)
	{
	case 1://Prikaz linije
		cout << *l << "\n";
		cout << "Unesite bilo koji broj da nastavite\n";
		cin >> number;
		break;
	case 2://Obrisi liniju
		n->removeLine(line);
		graphGenerated = false;
		break;
	case 3://Izmeni oznaku
		cout << "Unesite oznaku koju zelite da postavite\n";
		cin >> code;
		l->setCode(code);
		graphGenerated = false;
		break;
	case 4://Brisanje stajalista
		cout << "Unesite sifru stajalista koje zelite da obrisete\n";
		cin >> number;
		l->removeStation(number);
		graphGenerated = false;
		break;
	case 5://Dodavanje stajalista
		cout << "Unesite sifru stajalista koje zelite da dodate\n";
		cin >> number;
		s = Station::getStation(number);
		cout << "Unesite lokaciju u nizu u koju zelite da upisete stajaliste\n";
		cin >> number2;
		cout << "Unesite 1 za smer A, unesite 2 za smer B\n";
		cin >> number;
		if (number == 1)
			l->addStationToLocation(s, Direction::A, number2);
		if (number == 2)
			l->addStationToLocation(s, Direction::B, number2);
		graphGenerated = false;
		break;
	case 0:
		exitProgram(n);
		break;
	default:
		break;
	}
}

void lineManipulationText()
{
	clearScreen();
	cout << "Izaberite koju funkciju zelite da izvrsite\n";
	cout << "1. Prikaz linije\n";
	cout << "2. Obrisi liniju\n";
	cout << "3. Izmeni oznaku\n";
	cout << "4. Brisanje stajalista\n";
	cout << "5. Dodavanje stajalista\n"; 
	cout << "0. Izlaz\n";
}

void exitProgram(Network *n)
{
	int number;
	if (!graphGenerated)
	{
		cout << "Niste izgenerisali graf, ako to zelite pritisnite 1, ako ne 0\n";
		cin >> number;
		if (number == 1)
			graphGenerating(n);
	}
	cout << "Da li ste sigurni da zelite da izadjete\n1.DA\n2.NE";
	cin >> number;
	if (number == 2)
		return;
	exit(0);
}

void pauseScreen() {
	string pause;
	cout << "Unesite bilo koji karakter\n";
	cin >> pause;
	return;
}