#include "Line.h"
#ifndef __NETWORK_H_
#define __NETWORK_H_



class Network
{
public:
	Network();
	~Network();
	void addLine(Line* l);
	void removeLine(Line* l);
	void readLines();
	void readLine(string code);
	Line* parseLine(string line);
	void setZone(int zone);
	friend ostream& operator<<(ostream& it, const Network n);
	inline void setNumberMin(int number) { numberMin = number; }
	inline void setNumberMax(int number) { numberMax = number; }
	inline void setMaxNumberOfStations(int number) { maxNumberOfStations = number; }
	inline void setMinNumberOfStations(int number) { minNumberOfStations = number; }
private:
	vector<Line*> lines;
	int zone;
	int numberMin = 0;
	int numberMax = 200000;
	int maxNumberOfStations = 200000;
	int minNumberOfStations = 0;
};

#endif // !__NETWORK_H_