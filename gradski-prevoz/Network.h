#include "Line.h"
#ifndef __NETWORK_H_
#define __NETWORK_H_



class Network
{
public:
	Network();
	~Network();
	void addLine(Line* l);
	void readLines();
	Line* parseLine(string line);
	friend ostream& operator<<(ostream& it, const Network n);
private:
	vector<Line*> lines;
};

#endif // !__NETWORK_H_