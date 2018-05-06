#include "Line.h"
#include <unordered_set>

Line::Line(string code, string firstStop, string lastStop, int number)
{
	this->code = code;
	this->firstStop = firstStop;
	this->lastStop = lastStop;
	this->number = number;
}

Line::~Line()
{
	for (auto it = A_firstToLastStation.begin(); it != A_firstToLastStation.end(); ++it)
		delete *it;
	for (auto it = B_lastToFirstStation.begin(); it != B_lastToFirstStation.end(); ++it)
		delete *it;
	A_firstToLastStation.clear();
	B_lastToFirstStation.clear();	
}

void Line::addStationAndZone(Station *s, Direction d)
{
	addZone((*s).getZone());
	if (d==Direction::A)
		A_firstToLastStation.push_back(s);
	if (d==Direction::B)
		B_lastToFirstStation.push_back(s);
}

void Line::addZone(int zone)
{
	if (zone > this->zone)
		this->zone = zone;
}

void Line::removeStation(int code, Direction d)
{
	if (d == Direction::A)
	{
		int i = 0;
		for (Station* s : A_firstToLastStation)
		{
			if (code == (*s).getCode())
			{
				A_firstToLastStation.erase(A_firstToLastStation.begin() + i);
				return;
			}
			i++;
		}
	}

	if (d == Direction::B)
	{
		int i = 0;
		for (Station* s : B_lastToFirstStation)
		{
			if (code == (*s).getCode())
			{
				B_lastToFirstStation.erase(B_lastToFirstStation.begin() + i);
				return;
			}
			i++;
		}
	}
}

void Line::addStationToLocation(Station * s, Direction d, int location)
{
	if (d == Direction::A)
		A_firstToLastStation.insert(A_firstToLastStation.begin() + location, s);
	if (d == Direction::B)
		B_lastToFirstStation.insert(B_lastToFirstStation.begin() + location, s);
}

bool Line::isStationOnLine(int station, Direction d)
{
	if (d == Direction::A)
	{
		auto it = find_if(A_firstToLastStation.begin(), A_firstToLastStation.end(), [station](Station* s) {return (*s).getCode() == station; });
			if (it != A_firstToLastStation.end())
				return true;
			return false;
	}
	if (d == Direction::B)
	{
		auto it = find_if(B_lastToFirstStation.begin(), B_lastToFirstStation.end(), [station](Station* s) {return (*s).getCode() == station; });
		if (it != B_lastToFirstStation.end())
			return true;
		return false;
	}
	return false;
}

void Line::readStations(Direction d)
{
	ifstream dir;
	string fileName;
	if(d == Direction::A)
		fileName = "data\\" + code + "_dirA.txt";
	if(d == Direction::B)
		fileName = "data\\" + code + "_dirB.txt"; 
	dir.open(fileName);
	string lineInFile;
	if (dir.is_open())
	{
		while (getline(dir, lineInFile))
		{
			Station* station = parseStation(lineInFile);
			addStationAndZone(station, d);
			Station::addStationAndLine(station, this, code);
			station = nullptr;
		}
		dir.close();
	}
	else cout << "Unable to open file";
}

Station* Line::parseStation(string line)
{

	regex reg("([0-9]+)!(.+)!([0-9]+.[0-9]+)!([0-9]+.[0-9]+)!([0-9]+)");
	smatch result;
	if (regex_match(line, result, reg)) {

		int code = atoi(result.str(1).c_str());
		string name = result.str(2);
		double latitude = atof(result.str(3).c_str());
		double longitude = atof(result.str(4).c_str());
		int zone = atoi(result.str(5).c_str());
		Station* s = new Station(code, name, latitude, longitude, zone);
		return s;
	}
	else {
		cout << "No match" << endl;
		return nullptr;
	}
}

ostream & operator<<(ostream & it, const Line & l)
{
	it << "Linija: " << l.code;
	it << " Pocetno stajaliste: " << l.firstStop;
	it << " Poslednje stajaliste: " << l.lastStop;
	it << "\nSmer A\n";
	for (Station *s : l.A_firstToLastStation)
	{
		it << *s << "\n";
	}
	it << "Smer B\n";
	for (Station *s : l.B_lastToFirstStation)
	{
		it << *s << "\n";
	}
	return it;
}
