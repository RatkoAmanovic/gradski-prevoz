#include "Station.h"

unordered_map<int, Station*> Station::stations;

Station::Station(int code, string name, double latitude, double longitude, int zone)
{
	
	this->code = code;
	this->name = name;
	location = Location(latitude, longitude);
	this->zone = zone;
	while (this->zone < 1 || this->zone > 4)
		{
			cout << "Zona za stanicu "<<name<<" nije u opsegu, za ispravku uneti zeljenu zonu\n";
			cin >> this->zone;
		}
}

Station::~Station()
{
}

void Station::addStationAndLine(Station *s, Line *l, string lineCode)
{
	if ((*s).code == 64)
		cout << "fad";
	if (stations.find((*s).code) == stations.end())
		stations[(*s).code] = s;
	stations[(*s).code]->addLine(l, lineCode);
		
}


void Station::addLine(Line *l, string lineCode)
{
	if (lines.find(lineCode) == lines.end())
		lines[lineCode] = l;
}

ostream & operator<<(ostream & it, const Station & s)
{
	if (&s == nullptr)
	{
		cout << "Nema stanice";
		return it;
	}
	it << "Sifra: " << s.code;
	it << " Ime: " << s.name;
	it << " " << s.location;
	it << " Zona: " << s.zone;
	it << " Linije:";
	Station* station = Station::getStation(s.code);
	for (pair<string, Line*> line : (*station).lines)
	{
		it << " " << line.first;
	}
	return it;
}
