#include "Station.h"
#include <vector>

#ifndef __LINE_H_
#define __LINE_H_

class Line
{
public:
	Line(string code, string firstStop, string lastStop);

	~Line();

private:
	string code;
	string firstStop;
	string lastStop;
	vector<Station> firstToLastStation;
	vector<Station> lastToFirstStation;
};
#endif // !__LINE_H_
