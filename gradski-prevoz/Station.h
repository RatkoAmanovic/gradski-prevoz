#include <string>
#include <iostream>
#include <regex>
#include <unordered_map>

#include "Location.h"

#ifndef __STATION_H_
#define __STATION_H_
using namespace std;

class Line;

class Station
{
public:
	Station(int code, string name, double latitude, double longitude, int zone);
	~Station();
	friend ostream& operator<<(ostream& it, const Station &s);
	static void addStationAndLine(Station& s, Line& l, string lineCode);
	static Station& getStation(int code);
	void addLine(Line & l, string lineCode);

private:
	int code;
	string name;
	Location location;
	int zone;
	unordered_map<string,Line*> lines;
	static unordered_map<int,Station*> stations;
};

#endif // !__Station_H_
