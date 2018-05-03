#include "Network.h"

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
			network.readLines();
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