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
	static void addStationAndLine(Station *s, Line *l, string lineCode);
	friend ostream& operator<<(ostream& it, const Station &s);
	static Station* getStation(int code) { return stations[code]; }
	void addLine(Line *l, string lineCode);
	int getZone() { return zone; }
	int getCode() { return code; }
	static auto getStationsBegin() { return stations.begin(); }
	static auto getStationsEnd() { return stations.end(); }
	auto getLinesBegin() { return lines.begin(); }
	auto getLinesEnd() { return lines.end(); }
	bool isInLines(string line) { return lines.find(line) != lines.end(); }
	double getStationLatitude() { return location.getLatitude(); }
	double getStationLongitude() { return location.getLongitude(); }

private:
	int code;
	string name;
	Location location;
	int zone;
	unordered_map<string,Line*> lines;
	static unordered_map<int,Station*> stations;
};

#endif // !__Station_H_
