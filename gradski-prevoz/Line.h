#include "Station.h"
#include <vector>
#include <fstream>

using namespace std;

#ifndef __LINE_H_
#define __LINE_H_


enum Direction { A, B };

class Line
{
public:
	Line(string code, string firstStop, string lastStop);
	~Line();
	void addStationAndZone(Station * s, Direction d);
	friend ostream& operator<<(ostream& it, const Line& l);
	void readStations(Direction d);
	Station* parseStation(string line);
	string getCode() { return code; }
	void addZone(int zone);
	void removeStation(int code, Direction d);
	void addStationToLocation(Station *s, Direction d, int location);
	inline void setCode(int code) { this->code = code; }

private:
	string code;
	string firstStop;
	string lastStop;
	int zones[4] = {0,0,0,0};
	vector<Station*> A_firstToLastStation;
	vector<Station*> B_lastToFirstStation;
};
#endif // !__LINE_H_
