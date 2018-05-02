#include "Station.h"

Station::Station(int code, string name, double latitude, double longitude, int zone)
{

	this->code = code;
	this->name = name;
	location = Location(latitude, longitude);
	if (zone >= 1 || zone <= 4)
		this->zone = zone;
	else
	{
		while (zone < 1 || zone > 4)
		{
			cout << "Zona nije u opsegu, za ispravku uneti zeljenu zonu\n";
			cin >> this->zone;
		}
	}
}

Station::~Station()
{
}

ostream & operator<<(ostream & it, const Station & s)
{
	it << "Sifra: " << s.code;
	it << " Ime: " << s.name;
	it << " " << s.location;
	it << " Zona: " << s.zone;
	return it;
}