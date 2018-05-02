#include "Station.h"

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

Station* Station::parse(string line)
{
	
	regex reg("([0-9]+)!(.+)!([0-9]+.[0-9]+)!([0-9]+.[0-9]+)!([0-9]+)");
	smatch result;
		if (regex_match(line, result, reg)) {

			int code = atoi(result.str(1).c_str());
			string name = result.str(2);
			double latitude = atof(result.str(4).c_str());
			double longitude = atof(result.str(5).c_str());
			int zone = atoi(result.str(3).c_str());
			Station s(code, name, latitude, longitude, zone);
			return &s;
		}
		else {
			cout << "No match" << endl;
			return nullptr;
		}
}

ostream & operator<<(ostream & it, const Station & s)
{
	it << "Sifra: " << s.code;
	it << " Ime: " << s.name;
	it << " " << s.location;
	it << " Zona: " << s.zone;
	return it;
}
