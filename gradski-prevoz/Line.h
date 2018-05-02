#include "Station.h"
#include <vector>
#include <fstream>

using namespace std;

#ifndef __LINE_H_
#define __LINE_H_

class Line
{
public:
	Line(string code, string firstStop, string lastStop);
	~Line();
	friend ostream& operator<<(ostream& it, const Line& l);
	void addStationToA(const Station s);
	void addStationToB(const Station s);
	void readStationsToA();
	void readStationsToB();
private:
	string code;
	string firstStop;
	string lastStop;
	vector<Station> AfirstToLastStation;
	vector<Station> BlastToFirstStation;
};
#endif // !__LINE_H_
