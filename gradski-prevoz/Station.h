#include <string>
#include <iostream>

#include "Location.h"

#ifndef __Station_H_
#define __Station_H_

using namespace std;


class Station
{
public:
	Station(int code, string name, double latitude, double longitude, int zone);
	~Station();
	friend ostream& operator<<(ostream& it, const Station &s);

private:
	int code;
	string name;
	Location location;
	int zone;
};

#endif // !__Station_H_
