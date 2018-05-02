#include "Line.h"

class Network
{
public:
	Network();
	~Network();
	void addLine(const Line l);
	void readLines();
	Line parseLine(string line);
private:
	vector<Line> lines;
};

