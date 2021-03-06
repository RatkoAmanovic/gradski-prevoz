#include "Station.h"
#include <vector>
#include <fstream>
#include <unordered_set>

using namespace std;

#ifndef __LINE_H_
#define __LINE_H_


enum Direction { A, B };

class Line
{
public:
	Line(string code, string firstStop, string lastStop, int number);
	~Line();
	void addStationAndZone(Station * s, Direction d);
	friend ostream& operator<<(ostream& it, const Line& l);
	void readStations(Direction d);
	Station* parseStation(string line);
	inline string getCode() const { return code; }
	void addZone(int zone);
	void removeStation(int code);
	void addStationToLocation(Station *s, Direction d, int location);
	inline void setCode(string code) { this->code = code; }
	inline int getZone() const { return zone; }
	inline int getNumber() const { return number; }
	inline int getNumberOfStations() const { return A_firstToLastStation.size() + B_lastToFirstStation.size(); }
	bool isStationOnLine(int station, Direction d);
	auto getA_firstBegin() { return A_firstToLastStation.begin(); }
	auto getA_firstEnd() { return A_firstToLastStation.end(); }
	auto getB_lastBegin() { return B_lastToFirstStation.begin(); }
	auto getB_lastEnd() { return B_lastToFirstStation.end(); }
private:
	string code;
	string firstStop;
	string lastStop;
	int zone;
	int number;
	vector<Station*> A_firstToLastStation;
	vector<Station*> B_lastToFirstStation;
};
#endif // !__LINE_H_
